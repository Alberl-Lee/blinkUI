/*
 * Copyright (C) 2005, 2006 Apple Computer, Inc.  All rights reserved.
 * Copyright (C) 2009 Torch Mobile, Inc.
 * Copyright (C) 2013 Google Inc. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY APPLE COMPUTER, INC. ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL APPLE COMPUTER, INC. OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "platform/transforms/TransformationMatrix.h"
#if HAVE(MIPS_MSA_INTRINSICS)
#include "platform/cpu/mips/CommonMacrosMSA.h"
#endif

#include "platform/geometry/FloatBox.h"
#include "platform/geometry/FloatQuad.h"
#include "platform/geometry/FloatRect.h"
#include "platform/geometry/IntRect.h"
#include "platform/geometry/LayoutRect.h"
#include "platform/transforms/AffineTransform.h"
#include "platform/transforms/Rotation.h"

#include "wtf/Assertions.h"
#include "wtf/MathExtras.h"
#include "wtf/text/WTFString.h"

#include <cmath>
#include <cstdlib>

#if CPU(X86_64)
#include <emmintrin.h>
#endif

namespace blink {

//
// Supporting Math Functions
//
// This is a set of function from various places (attributed inline) to do
// things like inversion and decomposition of a 4x4 matrix. They are used
// throughout the code
//

//
// Adapted from Matrix Inversion by Richard Carling, Graphics Gems
// <http://tog.acm.org/GraphicsGems/index.html>.

// EULA: The Graphics Gems code is copyright-protected. In other words, you
// cannot claim the text of the code as your own and resell it. Using the code
// is permitted in any program, product, or library, non-commercial or
// commercial. Giving credit is not required, though is a nice gesture. The code
// comes as-is, and if there are any flaws or problems with any Gems code,
// nobody involved with Gems - authors, editors, publishers, or webmasters - are
// to be held responsible. Basically, don't be a jerk, and remember that
// anything free comes with no guarantee.

// A clarification about the storage of matrix elements
//
// This class uses a 2 dimensional array internally to store the elements of the
// matrix.  The first index into the array refers to the column that the element
// lies in; the second index refers to the row.
//
// In other words, this is the layout of the matrix:
//
// | m_matrix[0][0] m_matrix[1][0] m_matrix[2][0] m_matrix[3][0] |
// | m_matrix[0][1] m_matrix[1][1] m_matrix[2][1] m_matrix[3][1] |
// | m_matrix[0][2] m_matrix[1][2] m_matrix[2][2] m_matrix[3][2] |
// | m_matrix[0][3] m_matrix[1][3] m_matrix[2][3] m_matrix[3][3] |

typedef double Vector4[4];
typedef double Vector3[3];

const double SmallNumber = 1.e-8;

// inverse(original_matrix, inverse_matrix)
//
// calculate the inverse of a 4x4 matrix
//
// -1
// A  = ___1__ adjoint A
//       det A

//  double = determinant2x2(double a, double b, double c, double d)
//
//  calculate the determinant of a 2x2 matrix.

static double determinant2x2(double a, double b, double c, double d)
{
    return a * d - b * c;
}

//  double = determinant3x3(a1, a2, a3, b1, b2, b3, c1, c2, c3)
//
//  Calculate the determinant of a 3x3 matrix
//  in the form
//
//      | a1,  b1,  c1 |
//      | a2,  b2,  c2 |
//      | a3,  b3,  c3 |

static double determinant3x3(double a1,
    double a2,
    double a3,
    double b1,
    double b2,
    double b3,
    double c1,
    double c2,
    double c3)
{
    return a1 * determinant2x2(b2, b3, c2, c3) - b1 * determinant2x2(a2, a3, c2, c3) + c1 * determinant2x2(a2, a3, b2, b3);
}

//  double = determinant4x4(matrix)
//
//  calculate the determinant of a 4x4 matrix.

static double determinant4x4(const TransformationMatrix::Matrix4& m)
{
    // Assign to individual variable names to aid selecting
    // correct elements

    double a1 = m[0][0];
    double b1 = m[0][1];
    double c1 = m[0][2];
    double d1 = m[0][3];

    double a2 = m[1][0];
    double b2 = m[1][1];
    double c2 = m[1][2];
    double d2 = m[1][3];

    double a3 = m[2][0];
    double b3 = m[2][1];
    double c3 = m[2][2];
    double d3 = m[2][3];

    double a4 = m[3][0];
    double b4 = m[3][1];
    double c4 = m[3][2];
    double d4 = m[3][3];

    return a1 * determinant3x3(b2, b3, b4, c2, c3, c4, d2, d3, d4) - b1 * determinant3x3(a2, a3, a4, c2, c3, c4, d2, d3, d4) + c1 * determinant3x3(a2, a3, a4, b2, b3, b4, d2, d3, d4) - d1 * determinant3x3(a2, a3, a4, b2, b3, b4, c2, c3, c4);
}

#if !CPU(ARM64)
// adjoint( original_matrix, inverse_matrix )
//
//   calculate the adjoint of a 4x4 matrix
//
//    Let  a   denote the minor determinant of matrix A obtained by
//         ij
//
//    deleting the ith row and jth column from A.
//
//                  i+j
//   Let  b   = (-1)    a
//        ij            ji
//
//  The matrix B = (b  ) is the adjoint of A
//                   ij

static inline void adjoint(const TransformationMatrix::Matrix4& matrix,
    TransformationMatrix::Matrix4& result)
{
    // Assign to individual variable names to aid
    // selecting correct values
    double a1 = matrix[0][0];
    double b1 = matrix[0][1];
    double c1 = matrix[0][2];
    double d1 = matrix[0][3];

    double a2 = matrix[1][0];
    double b2 = matrix[1][1];
    double c2 = matrix[1][2];
    double d2 = matrix[1][3];

    double a3 = matrix[2][0];
    double b3 = matrix[2][1];
    double c3 = matrix[2][2];
    double d3 = matrix[2][3];

    double a4 = matrix[3][0];
    double b4 = matrix[3][1];
    double c4 = matrix[3][2];
    double d4 = matrix[3][3];

    // Row column labeling reversed since we transpose rows & columns
    result[0][0] = determinant3x3(b2, b3, b4, c2, c3, c4, d2, d3, d4);
    result[1][0] = -determinant3x3(a2, a3, a4, c2, c3, c4, d2, d3, d4);
    result[2][0] = determinant3x3(a2, a3, a4, b2, b3, b4, d2, d3, d4);
    result[3][0] = -determinant3x3(a2, a3, a4, b2, b3, b4, c2, c3, c4);

    result[0][1] = -determinant3x3(b1, b3, b4, c1, c3, c4, d1, d3, d4);
    result[1][1] = determinant3x3(a1, a3, a4, c1, c3, c4, d1, d3, d4);
    result[2][1] = -determinant3x3(a1, a3, a4, b1, b3, b4, d1, d3, d4);
    result[3][1] = determinant3x3(a1, a3, a4, b1, b3, b4, c1, c3, c4);

    result[0][2] = determinant3x3(b1, b2, b4, c1, c2, c4, d1, d2, d4);
    result[1][2] = -determinant3x3(a1, a2, a4, c1, c2, c4, d1, d2, d4);
    result[2][2] = determinant3x3(a1, a2, a4, b1, b2, b4, d1, d2, d4);
    result[3][2] = -determinant3x3(a1, a2, a4, b1, b2, b4, c1, c2, c4);

    result[0][3] = -determinant3x3(b1, b2, b3, c1, c2, c3, d1, d2, d3);
    result[1][3] = determinant3x3(a1, a2, a3, c1, c2, c3, d1, d2, d3);
    result[2][3] = -determinant3x3(a1, a2, a3, b1, b2, b3, d1, d2, d3);
    result[3][3] = determinant3x3(a1, a2, a3, b1, b2, b3, c1, c2, c3);
}
#endif

// Returns false if the matrix is not invertible
static bool inverse(const TransformationMatrix::Matrix4& matrix,
    TransformationMatrix::Matrix4& result)
{
    // Calculate the 4x4 determinant
    // If the determinant is zero,
    // then the inverse matrix is not unique.
    double det = determinant4x4(matrix);

    if (fabs(det) < SmallNumber)
        return false;

#if CPU(ARM64)
    double rdet = 1 / det;
    const double* mat = &(matrix[0][0]);
    double* pr = &(result[0][0]);
    asm volatile(
        // mat: v16 - v23
        // m11, m12, m13, m14
        // m21, m22, m23, m24
        // m31, m32, m33, m34
        // m41, m42, m43, m44
        "ld1 {v16.2d - v19.2d}, [%[mat]], 64  \n\t"
        "ld1 {v20.2d - v23.2d}, [%[mat]]      \n\t"
        "ins v30.d[0], %[rdet]         \n\t"
        // Determinant: right mat2x2
        "trn1 v0.2d, v17.2d, v21.2d    \n\t"
        "trn2 v1.2d, v19.2d, v23.2d    \n\t"
        "trn2 v2.2d, v17.2d, v21.2d    \n\t"
        "trn1 v3.2d, v19.2d, v23.2d    \n\t"
        "trn2 v5.2d, v21.2d, v23.2d    \n\t"
        "trn1 v4.2d, v17.2d, v19.2d    \n\t"
        "trn2 v6.2d, v17.2d, v19.2d    \n\t"
        "trn1 v7.2d, v21.2d, v23.2d    \n\t"
        "trn2 v25.2d, v23.2d, v21.2d   \n\t"
        "trn1 v27.2d, v23.2d, v21.2d   \n\t"
        "fmul v0.2d, v0.2d, v1.2d      \n\t"
        "fmul v1.2d, v4.2d, v5.2d      \n\t"
        "fmls v0.2d, v2.2d, v3.2d      \n\t"
        "fmul v2.2d, v4.2d, v25.2d     \n\t"
        "fmls v1.2d, v6.2d, v7.2d      \n\t"
        "fmls v2.2d, v6.2d, v27.2d     \n\t"
        // Adjoint:
        // v24: A11A12, v25: A13A14
        // v26: A21A22, v27: A23A24
        "fmul v3.2d, v18.2d, v0.d[1]   \n\t"
        "fmul v4.2d, v16.2d, v0.d[1]   \n\t"
        "fmul v5.2d, v16.2d, v1.d[1]   \n\t"
        "fmul v6.2d, v16.2d, v2.d[1]   \n\t"
        "fmls v3.2d, v20.2d, v1.d[1]   \n\t"
        "fmls v4.2d, v20.2d, v2.d[0]   \n\t"
        "fmls v5.2d, v18.2d, v2.d[0]   \n\t"
        "fmls v6.2d, v18.2d, v1.d[0]   \n\t"
        "fmla v3.2d, v22.2d, v2.d[1]   \n\t"
        "fmla v4.2d, v22.2d, v1.d[0]   \n\t"
        "fmla v5.2d, v22.2d, v0.d[0]   \n\t"
        "fmla v6.2d, v20.2d, v0.d[0]   \n\t"
        "fneg v3.2d, v3.2d             \n\t"
        "fneg v5.2d, v5.2d             \n\t"
        "trn1 v26.2d, v3.2d, v4.2d     \n\t"
        "trn1 v27.2d, v5.2d, v6.2d     \n\t"
        "trn2 v24.2d, v3.2d, v4.2d     \n\t"
        "trn2 v25.2d, v5.2d, v6.2d     \n\t"
        "fneg v24.2d, v24.2d           \n\t"
        "fneg v25.2d, v25.2d           \n\t"
        // Inverse
        // v24: I11I12, v25: I13I14
        // v26: I21I22, v27: I23I24
        "fmul v24.2d, v24.2d, v30.d[0] \n\t"
        "fmul v25.2d, v25.2d, v30.d[0] \n\t"
        "fmul v26.2d, v26.2d, v30.d[0] \n\t"
        "fmul v27.2d, v27.2d, v30.d[0] \n\t"
        "st1 {v24.2d - v27.2d}, [%[pr]], 64 \n\t"
        // Determinant: left mat2x2
        "trn1 v0.2d, v16.2d, v20.2d    \n\t"
        "trn2 v1.2d, v18.2d, v22.2d    \n\t"
        "trn2 v2.2d, v16.2d, v20.2d    \n\t"
        "trn1 v3.2d, v18.2d, v22.2d    \n\t"
        "trn2 v5.2d, v20.2d, v22.2d    \n\t"
        "trn1 v4.2d, v16.2d, v18.2d    \n\t"
        "trn2 v6.2d, v16.2d, v18.2d    \n\t"
        "trn1 v7.2d, v20.2d, v22.2d    \n\t"
        "trn2 v25.2d, v22.2d, v20.2d   \n\t"
        "trn1 v27.2d, v22.2d, v20.2d   \n\t"
        "fmul v0.2d, v0.2d, v1.2d      \n\t"
        "fmul v1.2d, v4.2d, v5.2d      \n\t"
        "fmls v0.2d, v2.2d, v3.2d      \n\t"
        "fmul v2.2d, v4.2d, v25.2d     \n\t"
        "fmls v1.2d, v6.2d, v7.2d      \n\t"
        "fmls v2.2d, v6.2d, v27.2d     \n\t"
        // Adjoint:
        // v24: A31A32, v25: A33A34
        // v26: A41A42, v27: A43A44
        "fmul v3.2d, v19.2d, v0.d[1]   \n\t"
        "fmul v4.2d, v17.2d, v0.d[1]   \n\t"
        "fmul v5.2d, v17.2d, v1.d[1]   \n\t"
        "fmul v6.2d, v17.2d, v2.d[1]   \n\t"
        "fmls v3.2d, v21.2d, v1.d[1]   \n\t"
        "fmls v4.2d, v21.2d, v2.d[0]   \n\t"
        "fmls v5.2d, v19.2d, v2.d[0]   \n\t"
        "fmls v6.2d, v19.2d, v1.d[0]   \n\t"
        "fmla v3.2d, v23.2d, v2.d[1]   \n\t"
        "fmla v4.2d, v23.2d, v1.d[0]   \n\t"
        "fmla v5.2d, v23.2d, v0.d[0]   \n\t"
        "fmla v6.2d, v21.2d, v0.d[0]   \n\t"
        "fneg v3.2d, v3.2d             \n\t"
        "fneg v5.2d, v5.2d             \n\t"
        "trn1 v26.2d, v3.2d, v4.2d     \n\t"
        "trn1 v27.2d, v5.2d, v6.2d     \n\t"
        "trn2 v24.2d, v3.2d, v4.2d     \n\t"
        "trn2 v25.2d, v5.2d, v6.2d     \n\t"
        "fneg v24.2d, v24.2d           \n\t"
        "fneg v25.2d, v25.2d           \n\t"
        // Inverse
        // v24: I31I32, v25: I33I34
        // v26: I41I42, v27: I43I44
        "fmul v24.2d, v24.2d, v30.d[0] \n\t"
        "fmul v25.2d, v25.2d, v30.d[0] \n\t"
        "fmul v26.2d, v26.2d, v30.d[0] \n\t"
        "fmul v27.2d, v27.2d, v30.d[0] \n\t"
        "st1 {v24.2d - v27.2d}, [%[pr]] \n\t"
        : [mat] "+r"(mat), [pr] "+r"(pr)
        : [rdet] "r"(rdet)
        : "memory", "v0", "v1", "v2", "v3", "v4", "v5", "v6", "v7", "v16", "v17",
        "v18", "v19", "v20", "v21", "v22", "v23", "24", "25", "v26", "v27",
        "v28", "v29", "v30");
#elif HAVE(MIPS_MSA_INTRINSICS)
    const double rDet = 1 / det;
    const double* mat = &(matrix[0][0]);
    v2f64 mat0, mat1, mat2, mat3, mat4, mat5, mat6, mat7;
    v2f64 rev2, rev3, rev4, rev5, rev6, rev7;
    v2f64 tmp0, tmp1, tmp2, tmp3, tmp4, tmp5, tmp6, tmp7;
    v2f64 det0, det1, det2, tmp8, tmp9, tmp10, tmp11;
    const v2f64 rdet = COPY_DOUBLE_TO_VECTOR(rDet);
    // mat0 mat1 --> m00 m01 m02 m03
    // mat2 mat3 --> m10 m11 m12 m13
    // mat4 mat5 --> m20 m21 m22 m23
    // mat6 mat7 --> m30 m31 m32 m33
    LD_DP8(mat, 2, mat0, mat1, mat2, mat3, mat4, mat5, mat6, mat7);

    // Right half
    rev3 = SLDI_D(mat3, mat3, 8); // m13 m12
    rev5 = SLDI_D(mat5, mat5, 8); // m23 m22
    rev7 = SLDI_D(mat7, mat7, 8); // m33 m32

    // 2*2 Determinants
    // for A00 & A01
    tmp0 = mat5 * rev7;
    tmp1 = mat3 * rev7;
    tmp2 = mat3 * rev5;
    // for A10 & A11
    tmp3 = mat1 * rev7;
    tmp4 = mat1 * rev5;
    // for A20 & A21
    tmp5 = mat1 * rev3;
    // for A30 & A31
    tmp6 = (v2f64)__msa_ilvr_d((v2i64)tmp1, (v2i64)tmp0);
    tmp7 = (v2f64)__msa_ilvl_d((v2i64)tmp1, (v2i64)tmp0);
    det0 = tmp6 - tmp7;
    tmp6 = (v2f64)__msa_ilvr_d((v2i64)tmp3, (v2i64)tmp2);
    tmp7 = (v2f64)__msa_ilvl_d((v2i64)tmp3, (v2i64)tmp2);
    det1 = tmp6 - tmp7;
    tmp6 = (v2f64)__msa_ilvr_d((v2i64)tmp5, (v2i64)tmp4);
    tmp7 = (v2f64)__msa_ilvl_d((v2i64)tmp5, (v2i64)tmp4);
    det2 = tmp6 - tmp7;

    // Co-factors
    tmp0 = mat0 * (v2f64)__msa_splati_d((v2i64)det0, 0);
    tmp1 = mat0 * (v2f64)__msa_splati_d((v2i64)det0, 1);
    tmp2 = mat0 * (v2f64)__msa_splati_d((v2i64)det1, 0);
    tmp3 = mat2 * (v2f64)__msa_splati_d((v2i64)det0, 0);
    tmp4 = mat2 * (v2f64)__msa_splati_d((v2i64)det1, 1);
    tmp5 = mat2 * (v2f64)__msa_splati_d((v2i64)det2, 0);
    tmp6 = mat4 * (v2f64)__msa_splati_d((v2i64)det0, 1);
    tmp7 = mat4 * (v2f64)__msa_splati_d((v2i64)det1, 1);
    tmp8 = mat4 * (v2f64)__msa_splati_d((v2i64)det2, 1);
    tmp9 = mat6 * (v2f64)__msa_splati_d((v2i64)det1, 0);
    tmp10 = mat6 * (v2f64)__msa_splati_d((v2i64)det2, 0);
    tmp11 = mat6 * (v2f64)__msa_splati_d((v2i64)det2, 1);

    tmp0 -= tmp7;
    tmp1 -= tmp4;
    tmp2 -= tmp5;
    tmp3 -= tmp6;
    tmp0 += tmp10;
    tmp1 += tmp11;
    tmp2 += tmp8;
    tmp3 += tmp9;

    // Multiply with 1/det
    tmp0 *= rdet;
    tmp1 *= rdet;
    tmp2 *= rdet;
    tmp3 *= rdet;

    // Inverse: Upper half
    result[0][0] = tmp3[1];
    result[0][1] = -tmp0[1];
    result[0][2] = tmp1[1];
    result[0][3] = -tmp2[1];
    result[1][0] = -tmp3[0];
    result[1][1] = tmp0[0];
    result[1][2] = -tmp1[0];
    result[1][3] = tmp2[0];
    // Left half
    rev2 = SLDI_D(mat2, mat2, 8); // m13 m12
    rev4 = SLDI_D(mat4, mat4, 8); // m23 m22
    rev6 = SLDI_D(mat6, mat6, 8); // m33 m32

    // 2*2 Determinants
    // for A00 & A01
    tmp0 = mat4 * rev6;
    tmp1 = mat2 * rev6;
    tmp2 = mat2 * rev4;
    // for A10 & A11
    tmp3 = mat0 * rev6;
    tmp4 = mat0 * rev4;
    // for A20 & A21
    tmp5 = mat0 * rev2;
    // for A30 & A31
    tmp6 = (v2f64)__msa_ilvr_d((v2i64)tmp1, (v2i64)tmp0);
    tmp7 = (v2f64)__msa_ilvl_d((v2i64)tmp1, (v2i64)tmp0);
    det0 = tmp6 - tmp7;
    tmp6 = (v2f64)__msa_ilvr_d((v2i64)tmp3, (v2i64)tmp2);
    tmp7 = (v2f64)__msa_ilvl_d((v2i64)tmp3, (v2i64)tmp2);
    det1 = tmp6 - tmp7;
    tmp6 = (v2f64)__msa_ilvr_d((v2i64)tmp5, (v2i64)tmp4);
    tmp7 = (v2f64)__msa_ilvl_d((v2i64)tmp5, (v2i64)tmp4);
    det2 = tmp6 - tmp7;

    // Co-factors
    tmp0 = mat3 * (v2f64)__msa_splati_d((v2i64)det0, 0);
    tmp1 = mat1 * (v2f64)__msa_splati_d((v2i64)det0, 1);
    tmp2 = mat1 * (v2f64)__msa_splati_d((v2i64)det0, 0);
    tmp3 = mat1 * (v2f64)__msa_splati_d((v2i64)det1, 0);
    tmp4 = mat3 * (v2f64)__msa_splati_d((v2i64)det1, 1);
    tmp5 = mat3 * (v2f64)__msa_splati_d((v2i64)det2, 0);
    tmp6 = mat5 * (v2f64)__msa_splati_d((v2i64)det0, 1);
    tmp7 = mat5 * (v2f64)__msa_splati_d((v2i64)det1, 1);
    tmp8 = mat5 * (v2f64)__msa_splati_d((v2i64)det2, 1);
    tmp9 = mat7 * (v2f64)__msa_splati_d((v2i64)det1, 0);
    tmp10 = mat7 * (v2f64)__msa_splati_d((v2i64)det2, 0);
    tmp11 = mat7 * (v2f64)__msa_splati_d((v2i64)det2, 1);
    tmp0 -= tmp6;
    tmp1 -= tmp4;
    tmp2 -= tmp7;
    tmp3 -= tmp5;
    tmp0 += tmp9;
    tmp1 += tmp11;
    tmp2 += tmp10;
    tmp3 += tmp8;

    // Multiply with 1/det
    tmp0 *= rdet;
    tmp1 *= rdet;
    tmp2 *= rdet;
    tmp3 *= rdet;

    // Inverse: Lower half
    result[2][0] = tmp0[1];
    result[2][1] = -tmp2[1];
    result[2][2] = tmp1[1];
    result[2][3] = -tmp3[1];
    result[3][0] = -tmp0[0];
    result[3][1] = tmp2[0];
    result[3][2] = -tmp1[0];
    result[3][3] = tmp3[0];
#else
    // Calculate the adjoint matrix
    adjoint(matrix, result);

    double rdet = 1 / det;

    // Scale the adjoint matrix to get the inverse
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            result[i][j] = result[i][j] * rdet;
#endif
    return true;
}

// End of code adapted from Matrix Inversion by Richard Carling

// Perform a decomposition on the passed matrix, return false if unsuccessful
// From Graphics Gems: unmatrix.c

// Transpose rotation portion of matrix a, return b
static void transposeMatrix4(const TransformationMatrix::Matrix4& a,
    TransformationMatrix::Matrix4& b)
{
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            b[i][j] = a[j][i];
}

// Multiply a homogeneous point by a matrix and return the transformed point
static void v4MulPointByMatrix(const Vector4 p,
    const TransformationMatrix::Matrix4& m,
    Vector4 result)
{
    result[0] = (p[0] * m[0][0]) + (p[1] * m[1][0]) + (p[2] * m[2][0]) + (p[3] * m[3][0]);
    result[1] = (p[0] * m[0][1]) + (p[1] * m[1][1]) + (p[2] * m[2][1]) + (p[3] * m[3][1]);
    result[2] = (p[0] * m[0][2]) + (p[1] * m[1][2]) + (p[2] * m[2][2]) + (p[3] * m[3][2]);
    result[3] = (p[0] * m[0][3]) + (p[1] * m[1][3]) + (p[2] * m[2][3]) + (p[3] * m[3][3]);
}

static double v3Length(Vector3 a)
{
    return std::sqrt((a[0] * a[0]) + (a[1] * a[1]) + (a[2] * a[2]));
}

static void v3Scale(Vector3 v, double desiredLength)
{
    double len = v3Length(v);
    if (len != 0) {
        double l = desiredLength / len;
        v[0] *= l;
        v[1] *= l;
        v[2] *= l;
    }
}

static double v3Dot(const Vector3 a, const Vector3 b)
{
    return (a[0] * b[0]) + (a[1] * b[1]) + (a[2] * b[2]);
}

// Make a linear combination of two vectors and return the result.
// result = (a * ascl) + (b * bscl)
static void v3Combine(const Vector3 a,
    const Vector3 b,
    Vector3 result,
    double ascl,
    double bscl)
{
    result[0] = (ascl * a[0]) + (bscl * b[0]);
    result[1] = (ascl * a[1]) + (bscl * b[1]);
    result[2] = (ascl * a[2]) + (bscl * b[2]);
}

// Return the cross product result = a cross b */
static void v3Cross(const Vector3 a, const Vector3 b, Vector3 result)
{
    result[0] = (a[1] * b[2]) - (a[2] * b[1]);
    result[1] = (a[2] * b[0]) - (a[0] * b[2]);
    result[2] = (a[0] * b[1]) - (a[1] * b[0]);
}

static bool decompose(const TransformationMatrix::Matrix4& mat,
    TransformationMatrix::DecomposedType& result)
{
    TransformationMatrix::Matrix4 localMatrix;
    memcpy(localMatrix, mat, sizeof(TransformationMatrix::Matrix4));

    // Normalize the matrix.
    if (localMatrix[3][3] == 0)
        return false;

    int i, j;
    for (i = 0; i < 4; i++)
        for (j = 0; j < 4; j++)
            localMatrix[i][j] /= localMatrix[3][3];

    // perspectiveMatrix is used to solve for perspective, but it also provides
    // an easy way to test for singularity of the upper 3x3 component.
    TransformationMatrix::Matrix4 perspectiveMatrix;
    memcpy(perspectiveMatrix, localMatrix, sizeof(TransformationMatrix::Matrix4));
    for (i = 0; i < 3; i++)
        perspectiveMatrix[i][3] = 0;
    perspectiveMatrix[3][3] = 1;

    if (determinant4x4(perspectiveMatrix) == 0)
        return false;

    // First, isolate perspective.  This is the messiest.
    if (localMatrix[0][3] != 0 || localMatrix[1][3] != 0 || localMatrix[2][3] != 0) {
        // rightHandSide is the right hand side of the equation.
        Vector4 rightHandSide;
        rightHandSide[0] = localMatrix[0][3];
        rightHandSide[1] = localMatrix[1][3];
        rightHandSide[2] = localMatrix[2][3];
        rightHandSide[3] = localMatrix[3][3];

        // Solve the equation by inverting perspectiveMatrix and multiplying
        // rightHandSide by the inverse.  (This is the easiest way, not
        // necessarily the best.)
        TransformationMatrix::Matrix4 inversePerspectiveMatrix,
            transposedInversePerspectiveMatrix;
        if (!inverse(perspectiveMatrix, inversePerspectiveMatrix))
            return false;
        transposeMatrix4(inversePerspectiveMatrix,
            transposedInversePerspectiveMatrix);

        Vector4 perspectivePoint;
        v4MulPointByMatrix(rightHandSide, transposedInversePerspectiveMatrix,
            perspectivePoint);

        result.perspectiveX = perspectivePoint[0];
        result.perspectiveY = perspectivePoint[1];
        result.perspectiveZ = perspectivePoint[2];
        result.perspectiveW = perspectivePoint[3];

        // Clear the perspective partition
        localMatrix[0][3] = localMatrix[1][3] = localMatrix[2][3] = 0;
        localMatrix[3][3] = 1;
    } else {
        // No perspective.
        result.perspectiveX = result.perspectiveY = result.perspectiveZ = 0;
        result.perspectiveW = 1;
    }

    // Next take care of translation (easy).
    result.translateX = localMatrix[3][0];
    localMatrix[3][0] = 0;
    result.translateY = localMatrix[3][1];
    localMatrix[3][1] = 0;
    result.translateZ = localMatrix[3][2];
    localMatrix[3][2] = 0;

    // Vector4 type and functions need to be added to the common set.
    Vector3 row[3], pdum3;

    // Now get scale and shear.
    for (i = 0; i < 3; i++) {
        row[i][0] = localMatrix[i][0];
        row[i][1] = localMatrix[i][1];
        row[i][2] = localMatrix[i][2];
    }

    // Compute X scale factor and normalize first row.
    result.scaleX = v3Length(row[0]);
    v3Scale(row[0], 1.0);

    // Compute XY shear factor and make 2nd row orthogonal to 1st.
    result.skewXY = v3Dot(row[0], row[1]);
    v3Combine(row[1], row[0], row[1], 1.0, -result.skewXY);

    // Now, compute Y scale and normalize 2nd row.
    result.scaleY = v3Length(row[1]);
    v3Scale(row[1], 1.0);
    result.skewXY /= result.scaleY;

    // Compute XZ and YZ shears, orthogonalize 3rd row.
    result.skewXZ = v3Dot(row[0], row[2]);
    v3Combine(row[2], row[0], row[2], 1.0, -result.skewXZ);
    result.skewYZ = v3Dot(row[1], row[2]);
    v3Combine(row[2], row[1], row[2], 1.0, -result.skewYZ);

    // Next, get Z scale and normalize 3rd row.
    result.scaleZ = v3Length(row[2]);
    v3Scale(row[2], 1.0);
    result.skewXZ /= result.scaleZ;
    result.skewYZ /= result.scaleZ;

    // At this point, the matrix (in rows[]) is orthonormal.
    // Check for a coordinate system flip.  If the determinant
    // is -1, then negate the matrix and the scaling factors.
    v3Cross(row[1], row[2], pdum3);
    if (v3Dot(row[0], pdum3) < 0) {
        result.scaleX *= -1;
        result.scaleY *= -1;
        result.scaleZ *= -1;

        for (i = 0; i < 3; i++) {
            row[i][0] *= -1;
            row[i][1] *= -1;
            row[i][2] *= -1;
        }
    }

    // Now, get the rotations out, as described in the gem.

    // FIXME - Add the ability to return either quaternions (which are
    // easier to recompose with) or Euler angles (rx, ry, rz), which
    // are easier for authors to deal with. The latter will only be useful
    // when we fix https://bugs.webkit.org/show_bug.cgi?id=23799, so I
    // will leave the Euler angle code here for now.

    // ret.rotateY = asin(-row[0][2]);
    // if (cos(ret.rotateY) != 0) {
    //     ret.rotateX = atan2(row[1][2], row[2][2]);
    //     ret.rotateZ = atan2(row[0][1], row[0][0]);
    // } else {
    //     ret.rotateX = atan2(-row[2][0], row[1][1]);
    //     ret.rotateZ = 0;
    // }

    double s, t, x, y, z, w;

    t = row[0][0] + row[1][1] + row[2][2] + 1.0;

    if (t > 1e-4) {
        s = 0.5 / std::sqrt(t);
        w = 0.25 / s;
        x = (row[2][1] - row[1][2]) * s;
        y = (row[0][2] - row[2][0]) * s;
        z = (row[1][0] - row[0][1]) * s;
    } else if (row[0][0] > row[1][1] && row[0][0] > row[2][2]) {
        s = std::sqrt(1.0 + row[0][0] - row[1][1] - row[2][2]) * 2.0; // S=4*qx
        x = 0.25 * s;
        y = (row[0][1] + row[1][0]) / s;
        z = (row[0][2] + row[2][0]) / s;
        w = (row[2][1] - row[1][2]) / s;
    } else if (row[1][1] > row[2][2]) {
        s = std::sqrt(1.0 + row[1][1] - row[0][0] - row[2][2]) * 2.0; // S=4*qy
        x = (row[0][1] + row[1][0]) / s;
        y = 0.25 * s;
        z = (row[1][2] + row[2][1]) / s;
        w = (row[0][2] - row[2][0]) / s;
    } else {
        s = std::sqrt(1.0 + row[2][2] - row[0][0] - row[1][1]) * 2.0; // S=4*qz
        x = (row[0][2] + row[2][0]) / s;
        y = (row[1][2] + row[2][1]) / s;
        z = 0.25 * s;
        w = (row[1][0] - row[0][1]) / s;
    }

    result.quaternionX = x;
    result.quaternionY = y;
    result.quaternionZ = z;
    result.quaternionW = w;

    return true;
}

// Perform a spherical linear interpolation between the two
// passed quaternions with 0 <= t <= 1
static void slerp(double qa[4], const double qb[4], double t)
{
    double ax, ay, az, aw;
    double bx, by, bz, bw;
    double cx, cy, cz, cw;
    double product;

    ax = qa[0];
    ay = qa[1];
    az = qa[2];
    aw = qa[3];
    bx = qb[0];
    by = qb[1];
    bz = qb[2];
    bw = qb[3];

    product = ax * bx + ay * by + az * bz + aw * bw;

    product = clampTo(product, -1.0, 1.0);

    const double epsilon = 1e-5;
    if (std::abs(product - 1.0) < epsilon) {
        // Result is qa, so just return
        return;
    }

    double denom = std::sqrt(1.0 - product * product);
    double theta = std::acos(product);
    double w = std::sin(t * theta) * (1.0 / denom);

    double scale1 = std::cos(t * theta) - product * w;
    double scale2 = w;

    cx = ax * scale1 + bx * scale2;
    cy = ay * scale1 + by * scale2;
    cz = az * scale1 + bz * scale2;
    cw = aw * scale1 + bw * scale2;

    qa[0] = cx;
    qa[1] = cy;
    qa[2] = cz;
    qa[3] = cw;
}

// End of Supporting Math Functions

TransformationMatrix::TransformationMatrix(const AffineTransform& t)
{
    checkAlignment();
    setMatrix(t.a(), t.b(), t.c(), t.d(), t.e(), t.f());
}

TransformationMatrix& TransformationMatrix::scale(double s)
{
    return scaleNonUniform(s, s);
}

FloatPoint TransformationMatrix::projectPoint(const FloatPoint& p,
    bool* clamped) const
{
    // This is basically raytracing. We have a point in the destination
    // plane with z=0, and we cast a ray parallel to the z-axis from that
    // point to find the z-position at which it intersects the z=0 plane
    // with the transform applied. Once we have that point we apply the
    // inverse transform to find the corresponding point in the source
    // space.
    //
    // Given a plane with normal Pn, and a ray starting at point R0 and
    // with direction defined by the vector Rd, we can find the
    // intersection point as a distance d from R0 in units of Rd by:
    //
    // d = -dot (Pn', R0) / dot (Pn', Rd)
    if (clamped)
        *clamped = false;

    if (m33() == 0) {
        // In this case, the projection plane is parallel to the ray we are trying
        // to trace, and there is no well-defined value for the projection.
        return FloatPoint();
    }

    double x = p.x();
    double y = p.y();
    double z = -(m13() * x + m23() * y + m43()) / m33();

    // FIXME: use multVecMatrix()
    double outX = x * m11() + y * m21() + z * m31() + m41();
    double outY = x * m12() + y * m22() + z * m32() + m42();

    double w = x * m14() + y * m24() + z * m34() + m44();
    if (w <= 0) {
        // Using int max causes overflow when other code uses the projected point.
        // To represent infinity yet reduce the risk of overflow, we use a large but
        // not-too-large number here when clamping.
        const int largeNumber = 100000000 / kFixedPointDenominator;
        outX = copysign(largeNumber, outX);
        outY = copysign(largeNumber, outY);
        if (clamped)
            *clamped = true;
    } else if (w != 1) {
        outX /= w;
        outY /= w;
    }

    return FloatPoint(static_cast<float>(outX), static_cast<float>(outY));
}

FloatQuad TransformationMatrix::projectQuad(const FloatQuad& q,
    bool* clamped) const
{
    FloatQuad projectedQuad;

    bool clamped1 = false;
    bool clamped2 = false;
    bool clamped3 = false;
    bool clamped4 = false;

    projectedQuad.setP1(projectPoint(q.p1(), &clamped1));
    projectedQuad.setP2(projectPoint(q.p2(), &clamped2));
    projectedQuad.setP3(projectPoint(q.p3(), &clamped3));
    projectedQuad.setP4(projectPoint(q.p4(), &clamped4));

    if (clamped)
        *clamped = clamped1 || clamped2 || clamped3 || clamped4;

    // If all points on the quad had w < 0, then the entire quad would not be
    // visible to the projected surface.
    bool everythingWasClipped = clamped1 && clamped2 && clamped3 && clamped4;
    if (everythingWasClipped)
        return FloatQuad();

    return projectedQuad;
}

static float clampEdgeValue(float f)
{
    ASSERT(!std_isnan(f));
    return clampTo(f, (-LayoutUnit::max() / 2).toFloat(),
        (LayoutUnit::max() / 2).toFloat());
}

LayoutRect TransformationMatrix::clampedBoundsOfProjectedQuad(
    const FloatQuad& q) const
{
    FloatRect mappedQuadBounds = projectQuad(q).boundingBox();

    float left = clampEdgeValue(floorf(mappedQuadBounds.x()));
    float top = clampEdgeValue(floorf(mappedQuadBounds.y()));

    float right;
    if (std_isinf(mappedQuadBounds.x()) && std_isinf(mappedQuadBounds.width()))
        right = (LayoutUnit::max() / 2).toFloat();
    else
        right = clampEdgeValue(ceilf(mappedQuadBounds.maxX()));

    float bottom;
    if (std_isinf(mappedQuadBounds.y()) && std_isinf(mappedQuadBounds.height()))
        bottom = (LayoutUnit::max() / 2).toFloat();
    else
        bottom = clampEdgeValue(ceilf(mappedQuadBounds.maxY()));

    return LayoutRect(LayoutUnit::clamp(left), LayoutUnit::clamp(top),
        LayoutUnit::clamp(right - left),
        LayoutUnit::clamp(bottom - top));
}

void TransformationMatrix::transformBox(FloatBox& box) const
{
    FloatBox bounds;
    bool firstPoint = true;
    for (size_t i = 0; i < 2; ++i) {
        for (size_t j = 0; j < 2; ++j) {
            for (size_t k = 0; k < 2; ++k) {
                FloatPoint3D point(box.x(), box.y(), box.z());
                point += FloatPoint3D(i * box.width(), j * box.height(), k * box.depth());
                point = mapPoint(point);
                if (firstPoint) {
                    bounds.setOrigin(point);
                    firstPoint = false;
                } else {
                    bounds.expandTo(point);
                }
            }
        }
    }
    box = bounds;
}

FloatPoint TransformationMatrix::mapPoint(const FloatPoint& p) const
{
    if (isIdentityOrTranslation())
        return FloatPoint(p.x() + static_cast<float>(m_matrix[3][0]),
            p.y() + static_cast<float>(m_matrix[3][1]));

    return internalMapPoint(p);
}

FloatPoint3D TransformationMatrix::mapPoint(const FloatPoint3D& p) const
{
    if (isIdentityOrTranslation())
        return FloatPoint3D(p.x() + static_cast<float>(m_matrix[3][0]),
            p.y() + static_cast<float>(m_matrix[3][1]),
            p.z() + static_cast<float>(m_matrix[3][2]));

    return internalMapPoint(p);
}

IntRect TransformationMatrix::mapRect(const IntRect& rect) const
{
    return enclosingIntRect(mapRect(FloatRect(rect)));
}

LayoutRect TransformationMatrix::mapRect(const LayoutRect& r) const
{
    return enclosingLayoutRect(mapRect(FloatRect(r)));
}

FloatRect TransformationMatrix::mapRect(const FloatRect& r) const
{
    if (isIdentityOrTranslation()) {
        FloatRect mappedRect(r);
        mappedRect.move(static_cast<float>(m_matrix[3][0]),
            static_cast<float>(m_matrix[3][1]));
        return mappedRect;
    }

    FloatQuad result;

    float maxX = r.maxX();
    float maxY = r.maxY();
    result.setP1(internalMapPoint(FloatPoint(r.x(), r.y())));
    result.setP2(internalMapPoint(FloatPoint(maxX, r.y())));
    result.setP3(internalMapPoint(FloatPoint(maxX, maxY)));
    result.setP4(internalMapPoint(FloatPoint(r.x(), maxY)));

    return result.boundingBox();
}

FloatQuad TransformationMatrix::mapQuad(const FloatQuad& q) const
{
    if (isIdentityOrTranslation()) {
        FloatQuad mappedQuad(q);
        mappedQuad.move(static_cast<float>(m_matrix[3][0]),
            static_cast<float>(m_matrix[3][1]));
        return mappedQuad;
    }

    FloatQuad result;
    result.setP1(internalMapPoint(q.p1()));
    result.setP2(internalMapPoint(q.p2()));
    result.setP3(internalMapPoint(q.p3()));
    result.setP4(internalMapPoint(q.p4()));
    return result;
}

TransformationMatrix& TransformationMatrix::scaleNonUniform(double sx,
    double sy)
{
    m_matrix[0][0] *= sx;
    m_matrix[0][1] *= sx;
    m_matrix[0][2] *= sx;
    m_matrix[0][3] *= sx;

    m_matrix[1][0] *= sy;
    m_matrix[1][1] *= sy;
    m_matrix[1][2] *= sy;
    m_matrix[1][3] *= sy;
    return *this;
}

TransformationMatrix& TransformationMatrix::scale3d(double sx,
    double sy,
    double sz)
{
    scaleNonUniform(sx, sy);

    m_matrix[2][0] *= sz;
    m_matrix[2][1] *= sz;
    m_matrix[2][2] *= sz;
    m_matrix[2][3] *= sz;
    return *this;
}

TransformationMatrix& TransformationMatrix::rotate3d(const Rotation& rotation)
{
    return rotate3d(rotation.axis.x(), rotation.axis.y(), rotation.axis.z(),
        rotation.angle);
}

TransformationMatrix& TransformationMatrix::rotate3d(double x,
    double y,
    double z,
    double angle)
{
    // Normalize the axis of rotation
    double length = std::sqrt(x * x + y * y + z * z);
    if (length == 0) {
        // A direction vector that cannot be normalized, such as [0, 0, 0], will
        // cause the rotation to not be applied.
        return *this;
    } else if (length != 1) {
        x /= length;
        y /= length;
        z /= length;
    }

    // Angles are in degrees. Switch to radians.
    angle = deg2rad(angle);

    double sinTheta = std::sin(angle);
    double cosTheta = std::cos(angle);

    TransformationMatrix mat;

    // Optimize cases where the axis is along a major axis
    if (x == 1.0 && y == 0.0 && z == 0.0) {
        mat.m_matrix[0][0] = 1.0;
        mat.m_matrix[0][1] = 0.0;
        mat.m_matrix[0][2] = 0.0;
        mat.m_matrix[1][0] = 0.0;
        mat.m_matrix[1][1] = cosTheta;
        mat.m_matrix[1][2] = sinTheta;
        mat.m_matrix[2][0] = 0.0;
        mat.m_matrix[2][1] = -sinTheta;
        mat.m_matrix[2][2] = cosTheta;
        mat.m_matrix[0][3] = mat.m_matrix[1][3] = mat.m_matrix[2][3] = 0.0;
        mat.m_matrix[3][0] = mat.m_matrix[3][1] = mat.m_matrix[3][2] = 0.0;
        mat.m_matrix[3][3] = 1.0;
    } else if (x == 0.0 && y == 1.0 && z == 0.0) {
        mat.m_matrix[0][0] = cosTheta;
        mat.m_matrix[0][1] = 0.0;
        mat.m_matrix[0][2] = -sinTheta;
        mat.m_matrix[1][0] = 0.0;
        mat.m_matrix[1][1] = 1.0;
        mat.m_matrix[1][2] = 0.0;
        mat.m_matrix[2][0] = sinTheta;
        mat.m_matrix[2][1] = 0.0;
        mat.m_matrix[2][2] = cosTheta;
        mat.m_matrix[0][3] = mat.m_matrix[1][3] = mat.m_matrix[2][3] = 0.0;
        mat.m_matrix[3][0] = mat.m_matrix[3][1] = mat.m_matrix[3][2] = 0.0;
        mat.m_matrix[3][3] = 1.0;
    } else if (x == 0.0 && y == 0.0 && z == 1.0) {
        mat.m_matrix[0][0] = cosTheta;
        mat.m_matrix[0][1] = sinTheta;
        mat.m_matrix[0][2] = 0.0;
        mat.m_matrix[1][0] = -sinTheta;
        mat.m_matrix[1][1] = cosTheta;
        mat.m_matrix[1][2] = 0.0;
        mat.m_matrix[2][0] = 0.0;
        mat.m_matrix[2][1] = 0.0;
        mat.m_matrix[2][2] = 1.0;
        mat.m_matrix[0][3] = mat.m_matrix[1][3] = mat.m_matrix[2][3] = 0.0;
        mat.m_matrix[3][0] = mat.m_matrix[3][1] = mat.m_matrix[3][2] = 0.0;
        mat.m_matrix[3][3] = 1.0;
    } else {
        // This case is the rotation about an arbitrary unit vector.
        //
        // Formula is adapted from Wikipedia article on Rotation matrix,
        // http://en.wikipedia.org/wiki/Rotation_matrix#Rotation_matrix_from_axis_and_angle
        //
        // An alternate resource with the same matrix:
        // http://www.fastgraph.com/makegames/3drotation/
        //
        double oneMinusCosTheta = 1 - cosTheta;
        mat.m_matrix[0][0] = cosTheta + x * x * oneMinusCosTheta;
        mat.m_matrix[0][1] = y * x * oneMinusCosTheta + z * sinTheta;
        mat.m_matrix[0][2] = z * x * oneMinusCosTheta - y * sinTheta;
        mat.m_matrix[1][0] = x * y * oneMinusCosTheta - z * sinTheta;
        mat.m_matrix[1][1] = cosTheta + y * y * oneMinusCosTheta;
        mat.m_matrix[1][2] = z * y * oneMinusCosTheta + x * sinTheta;
        mat.m_matrix[2][0] = x * z * oneMinusCosTheta + y * sinTheta;
        mat.m_matrix[2][1] = y * z * oneMinusCosTheta - x * sinTheta;
        mat.m_matrix[2][2] = cosTheta + z * z * oneMinusCosTheta;
        mat.m_matrix[0][3] = mat.m_matrix[1][3] = mat.m_matrix[2][3] = 0.0;
        mat.m_matrix[3][0] = mat.m_matrix[3][1] = mat.m_matrix[3][2] = 0.0;
        mat.m_matrix[3][3] = 1.0;
    }
    multiply(mat);
    return *this;
}

TransformationMatrix& TransformationMatrix::rotate3d(double rx,
    double ry,
    double rz)
{
    // Angles are in degrees. Switch to radians.
    rx = deg2rad(rx);
    ry = deg2rad(ry);
    rz = deg2rad(rz);

    TransformationMatrix mat;

    double sinTheta = std::sin(rz);
    double cosTheta = std::cos(rz);

    mat.m_matrix[0][0] = cosTheta;
    mat.m_matrix[0][1] = sinTheta;
    mat.m_matrix[0][2] = 0.0;
    mat.m_matrix[1][0] = -sinTheta;
    mat.m_matrix[1][1] = cosTheta;
    mat.m_matrix[1][2] = 0.0;
    mat.m_matrix[2][0] = 0.0;
    mat.m_matrix[2][1] = 0.0;
    mat.m_matrix[2][2] = 1.0;
    mat.m_matrix[0][3] = mat.m_matrix[1][3] = mat.m_matrix[2][3] = 0.0;
    mat.m_matrix[3][0] = mat.m_matrix[3][1] = mat.m_matrix[3][2] = 0.0;
    mat.m_matrix[3][3] = 1.0;

    TransformationMatrix rmat(mat);

    sinTheta = std::sin(ry);
    cosTheta = std::cos(ry);

    mat.m_matrix[0][0] = cosTheta;
    mat.m_matrix[0][1] = 0.0;
    mat.m_matrix[0][2] = -sinTheta;
    mat.m_matrix[1][0] = 0.0;
    mat.m_matrix[1][1] = 1.0;
    mat.m_matrix[1][2] = 0.0;
    mat.m_matrix[2][0] = sinTheta;
    mat.m_matrix[2][1] = 0.0;
    mat.m_matrix[2][2] = cosTheta;
    mat.m_matrix[0][3] = mat.m_matrix[1][3] = mat.m_matrix[2][3] = 0.0;
    mat.m_matrix[3][0] = mat.m_matrix[3][1] = mat.m_matrix[3][2] = 0.0;
    mat.m_matrix[3][3] = 1.0;

    rmat.multiply(mat);

    sinTheta = std::sin(rx);
    cosTheta = std::cos(rx);

    mat.m_matrix[0][0] = 1.0;
    mat.m_matrix[0][1] = 0.0;
    mat.m_matrix[0][2] = 0.0;
    mat.m_matrix[1][0] = 0.0;
    mat.m_matrix[1][1] = cosTheta;
    mat.m_matrix[1][2] = sinTheta;
    mat.m_matrix[2][0] = 0.0;
    mat.m_matrix[2][1] = -sinTheta;
    mat.m_matrix[2][2] = cosTheta;
    mat.m_matrix[0][3] = mat.m_matrix[1][3] = mat.m_matrix[2][3] = 0.0;
    mat.m_matrix[3][0] = mat.m_matrix[3][1] = mat.m_matrix[3][2] = 0.0;
    mat.m_matrix[3][3] = 1.0;

    rmat.multiply(mat);

    multiply(rmat);
    return *this;
}

TransformationMatrix& TransformationMatrix::translate(double tx, double ty)
{
    m_matrix[3][0] += tx * m_matrix[0][0] + ty * m_matrix[1][0];
    m_matrix[3][1] += tx * m_matrix[0][1] + ty * m_matrix[1][1];
    m_matrix[3][2] += tx * m_matrix[0][2] + ty * m_matrix[1][2];
    m_matrix[3][3] += tx * m_matrix[0][3] + ty * m_matrix[1][3];
    return *this;
}

TransformationMatrix& TransformationMatrix::translate3d(double tx,
    double ty,
    double tz)
{
    m_matrix[3][0] += tx * m_matrix[0][0] + ty * m_matrix[1][0] + tz * m_matrix[2][0];
    m_matrix[3][1] += tx * m_matrix[0][1] + ty * m_matrix[1][1] + tz * m_matrix[2][1];
    m_matrix[3][2] += tx * m_matrix[0][2] + ty * m_matrix[1][2] + tz * m_matrix[2][2];
    m_matrix[3][3] += tx * m_matrix[0][3] + ty * m_matrix[1][3] + tz * m_matrix[2][3];
    return *this;
}

TransformationMatrix& TransformationMatrix::translateRight(double tx,
    double ty)
{
    if (tx != 0) {
        m_matrix[0][0] += m_matrix[0][3] * tx;
        m_matrix[1][0] += m_matrix[1][3] * tx;
        m_matrix[2][0] += m_matrix[2][3] * tx;
        m_matrix[3][0] += m_matrix[3][3] * tx;
    }

    if (ty != 0) {
        m_matrix[0][1] += m_matrix[0][3] * ty;
        m_matrix[1][1] += m_matrix[1][3] * ty;
        m_matrix[2][1] += m_matrix[2][3] * ty;
        m_matrix[3][1] += m_matrix[3][3] * ty;
    }

    return *this;
}

TransformationMatrix& TransformationMatrix::translateRight3d(double tx,
    double ty,
    double tz)
{
    translateRight(tx, ty);
    if (tz != 0) {
        m_matrix[0][2] += m_matrix[0][3] * tz;
        m_matrix[1][2] += m_matrix[1][3] * tz;
        m_matrix[2][2] += m_matrix[2][3] * tz;
        m_matrix[3][2] += m_matrix[3][3] * tz;
    }

    return *this;
}

TransformationMatrix& TransformationMatrix::skew(double sx, double sy)
{
    // angles are in degrees. Switch to radians
    sx = deg2rad(sx);
    sy = deg2rad(sy);

    TransformationMatrix mat;
    mat.m_matrix[0][1] = std::tan(sy); // note that the y shear goes in the first row
    mat.m_matrix[1][0] = std::tan(sx); // and the x shear in the second row

    multiply(mat);
    return *this;
}

TransformationMatrix& TransformationMatrix::applyPerspective(double p)
{
    TransformationMatrix mat;
    if (p != 0)
        mat.m_matrix[2][3] = -1 / p;

    multiply(mat);
    return *this;
}

TransformationMatrix& TransformationMatrix::applyTransformOrigin(double x,
    double y,
    double z)
{
    translateRight3d(x, y, z);
    translate3d(-x, -y, -z);
    return *this;
}

TransformationMatrix& TransformationMatrix::zoom(double zoomFactor)
{
    m_matrix[0][3] /= zoomFactor;
    m_matrix[1][3] /= zoomFactor;
    m_matrix[2][3] /= zoomFactor;
    m_matrix[3][0] *= zoomFactor;
    m_matrix[3][1] *= zoomFactor;
    m_matrix[3][2] *= zoomFactor;
    return *this;
}

// Calculates *this = *this * mat.
// Note: A * B means that the transforms represented by A happen first, and
// then the transforms represented by B. That is, the matrix A * B corresponds
// to a CSS transform list <transform-function-A> <transform-function-B>.
// Some branches of this function may make use of the fact that
// transpose(A * B) == transpose(B) * transpose(A); remember that
// m_matrix[a][b] is matrix element row b, col a.
// FIXME: As of 2016-05-04, the ARM64 branch is NOT triggered by tests on the CQ
// bots, see crbug.com/477892 and crbug.com/584508.
TransformationMatrix& TransformationMatrix::multiply(
    const TransformationMatrix& mat)
{
#if CPU(ARM64)
    double* rightMatrix = &(m_matrix[0][0]);
    const double* leftMatrix = &(mat.m_matrix[0][0]);
    asm volatile(
        // Load mat.m_matrix to v16 - v23.
        // Load this.m_matrix to v24 - v31.
        // Result: this = mat * this
        // | v0, v1 |   | v16, v17 |   | v24, v25 |
        // | v2, v3 | = | v18, v19 | * | v26, v27 |
        // | v4, v5 |   | v20, v21 |   | v28, v29 |
        // | v6, v7 |   | v22, v23 |   | v30, v31 |
        "mov x9, %[rightMatrix]   \t\n"
        "ld1 {v16.2d - v19.2d}, [%[leftMatrix]], 64  \t\n"
        "ld1 {v20.2d - v23.2d}, [%[leftMatrix]]      \t\n"
        "ld1 {v24.2d - v27.2d}, [%[rightMatrix]], 64 \t\n"
        "ld1 {v28.2d - v31.2d}, [%[rightMatrix]]     \t\n"

        "fmul v0.2d, v24.2d, v16.d[0]  \t\n"
        "fmul v1.2d, v25.2d, v16.d[0]  \t\n"
        "fmul v2.2d, v24.2d, v18.d[0]  \t\n"
        "fmul v3.2d, v25.2d, v18.d[0]  \t\n"
        "fmul v4.2d, v24.2d, v20.d[0]  \t\n"
        "fmul v5.2d, v25.2d, v20.d[0]  \t\n"
        "fmul v6.2d, v24.2d, v22.d[0]  \t\n"
        "fmul v7.2d, v25.2d, v22.d[0]  \t\n"

        "fmla v0.2d, v26.2d, v16.d[1]  \t\n"
        "fmla v1.2d, v27.2d, v16.d[1]  \t\n"
        "fmla v2.2d, v26.2d, v18.d[1]  \t\n"
        "fmla v3.2d, v27.2d, v18.d[1]  \t\n"
        "fmla v4.2d, v26.2d, v20.d[1]  \t\n"
        "fmla v5.2d, v27.2d, v20.d[1]  \t\n"
        "fmla v6.2d, v26.2d, v22.d[1]  \t\n"
        "fmla v7.2d, v27.2d, v22.d[1]  \t\n"

        "fmla v0.2d, v28.2d, v17.d[0]  \t\n"
        "fmla v1.2d, v29.2d, v17.d[0]  \t\n"
        "fmla v2.2d, v28.2d, v19.d[0]  \t\n"
        "fmla v3.2d, v29.2d, v19.d[0]  \t\n"
        "fmla v4.2d, v28.2d, v21.d[0]  \t\n"
        "fmla v5.2d, v29.2d, v21.d[0]  \t\n"
        "fmla v6.2d, v28.2d, v23.d[0]  \t\n"
        "fmla v7.2d, v29.2d, v23.d[0]  \t\n"

        "fmla v0.2d, v30.2d, v17.d[1]  \t\n"
        "fmla v1.2d, v31.2d, v17.d[1]  \t\n"
        "fmla v2.2d, v30.2d, v19.d[1]  \t\n"
        "fmla v3.2d, v31.2d, v19.d[1]  \t\n"
        "fmla v4.2d, v30.2d, v21.d[1]  \t\n"
        "fmla v5.2d, v31.2d, v21.d[1]  \t\n"
        "fmla v6.2d, v30.2d, v23.d[1]  \t\n"
        "fmla v7.2d, v31.2d, v23.d[1]  \t\n"

        "st1 {v0.2d - v3.2d}, [x9], 64 \t\n"
        "st1 {v4.2d - v7.2d}, [x9]     \t\n"
        : [leftMatrix] "+r"(leftMatrix), [rightMatrix] "+r"(rightMatrix)
        :
        : "memory", "x9", "v16", "v17", "v18", "v19", "v20", "v21", "v22", "v23",
        "v24", "v25", "v26", "v27", "v28", "v29", "v30", "v31", "v0", "v1",
        "v2", "v3", "v4", "v5", "v6", "v7");
#elif HAVE(MIPS_MSA_INTRINSICS)
    v2f64 vleftM0, vleftM1, vleftM2, vleftM3, vleftM4, vleftM5, vleftM6, vleftM7;
    v2f64 vRightM0, vRightM1, vRightM2, vRightM3, vRightM4, vRightM5, vRightM6,
        vRightM7;
    v2f64 vTmpM0, vTmpM1, vTmpM2, vTmpM3;

    vRightM0 = LD_DP(&(m_matrix[0][0]));
    vRightM1 = LD_DP(&(m_matrix[0][2]));
    vRightM2 = LD_DP(&(m_matrix[1][0]));
    vRightM3 = LD_DP(&(m_matrix[1][2]));
    vRightM4 = LD_DP(&(m_matrix[2][0]));
    vRightM5 = LD_DP(&(m_matrix[2][2]));
    vRightM6 = LD_DP(&(m_matrix[3][0]));
    vRightM7 = LD_DP(&(m_matrix[3][2]));

    vleftM0 = LD_DP(&(mat.m_matrix[0][0]));
    vleftM2 = LD_DP(&(mat.m_matrix[0][2]));
    vleftM4 = LD_DP(&(mat.m_matrix[1][0]));
    vleftM6 = LD_DP(&(mat.m_matrix[1][2]));

    vleftM1 = (v2f64)__msa_splati_d((v2i64)vleftM0, 1);
    vleftM0 = (v2f64)__msa_splati_d((v2i64)vleftM0, 0);
    vleftM3 = (v2f64)__msa_splati_d((v2i64)vleftM2, 1);
    vleftM2 = (v2f64)__msa_splati_d((v2i64)vleftM2, 0);
    vleftM5 = (v2f64)__msa_splati_d((v2i64)vleftM4, 1);
    vleftM4 = (v2f64)__msa_splati_d((v2i64)vleftM4, 0);
    vleftM7 = (v2f64)__msa_splati_d((v2i64)vleftM6, 1);
    vleftM6 = (v2f64)__msa_splati_d((v2i64)vleftM6, 0);

    vTmpM0 = vleftM0 * vRightM0;
    vTmpM1 = vleftM0 * vRightM1;
    vTmpM0 += vleftM1 * vRightM2;
    vTmpM1 += vleftM1 * vRightM3;
    vTmpM0 += vleftM2 * vRightM4;
    vTmpM1 += vleftM2 * vRightM5;
    vTmpM0 += vleftM3 * vRightM6;
    vTmpM1 += vleftM3 * vRightM7;

    vTmpM2 = vleftM4 * vRightM0;
    vTmpM3 = vleftM4 * vRightM1;
    vTmpM2 += vleftM5 * vRightM2;
    vTmpM3 += vleftM5 * vRightM3;
    vTmpM2 += vleftM6 * vRightM4;
    vTmpM3 += vleftM6 * vRightM5;
    vTmpM2 += vleftM7 * vRightM6;
    vTmpM3 += vleftM7 * vRightM7;

    vleftM0 = LD_DP(&(mat.m_matrix[2][0]));
    vleftM2 = LD_DP(&(mat.m_matrix[2][2]));
    vleftM4 = LD_DP(&(mat.m_matrix[3][0]));
    vleftM6 = LD_DP(&(mat.m_matrix[3][2]));

    ST_DP(vTmpM0, &(m_matrix[0][0]));
    ST_DP(vTmpM1, &(m_matrix[0][2]));
    ST_DP(vTmpM2, &(m_matrix[1][0]));
    ST_DP(vTmpM3, &(m_matrix[1][2]));

    vleftM1 = (v2f64)__msa_splati_d((v2i64)vleftM0, 1);
    vleftM0 = (v2f64)__msa_splati_d((v2i64)vleftM0, 0);
    vleftM3 = (v2f64)__msa_splati_d((v2i64)vleftM2, 1);
    vleftM2 = (v2f64)__msa_splati_d((v2i64)vleftM2, 0);
    vleftM5 = (v2f64)__msa_splati_d((v2i64)vleftM4, 1);
    vleftM4 = (v2f64)__msa_splati_d((v2i64)vleftM4, 0);
    vleftM7 = (v2f64)__msa_splati_d((v2i64)vleftM6, 1);
    vleftM6 = (v2f64)__msa_splati_d((v2i64)vleftM6, 0);

    vTmpM0 = vleftM0 * vRightM0;
    vTmpM1 = vleftM0 * vRightM1;
    vTmpM0 += vleftM1 * vRightM2;
    vTmpM1 += vleftM1 * vRightM3;
    vTmpM0 += vleftM2 * vRightM4;
    vTmpM1 += vleftM2 * vRightM5;
    vTmpM0 += vleftM3 * vRightM6;
    vTmpM1 += vleftM3 * vRightM7;

    vTmpM2 = vleftM4 * vRightM0;
    vTmpM3 = vleftM4 * vRightM1;
    vTmpM2 += vleftM5 * vRightM2;
    vTmpM3 += vleftM5 * vRightM3;
    vTmpM2 += vleftM6 * vRightM4;
    vTmpM3 += vleftM6 * vRightM5;
    vTmpM2 += vleftM7 * vRightM6;
    vTmpM3 += vleftM7 * vRightM7;

    ST_DP(vTmpM0, &(m_matrix[2][0]));
    ST_DP(vTmpM1, &(m_matrix[2][2]));
    ST_DP(vTmpM2, &(m_matrix[3][0]));
    ST_DP(vTmpM3, &(m_matrix[3][2]));
#elif defined(TRANSFORMATION_MATRIX_USE_X86_64_SSE2)
    // x86_64 has 16 XMM registers which is enough to do the multiplication fully
    // in registers.
    __m128d matrixBlockA = _mm_load_pd(&(m_matrix[0][0]));
    __m128d matrixBlockC = _mm_load_pd(&(m_matrix[1][0]));
    __m128d matrixBlockE = _mm_load_pd(&(m_matrix[2][0]));
    __m128d matrixBlockG = _mm_load_pd(&(m_matrix[3][0]));

    // First row.
    __m128d otherMatrixFirstParam = _mm_set1_pd(mat.m_matrix[0][0]);
    __m128d otherMatrixSecondParam = _mm_set1_pd(mat.m_matrix[0][1]);
    __m128d otherMatrixThirdParam = _mm_set1_pd(mat.m_matrix[0][2]);
    __m128d otherMatrixFourthParam = _mm_set1_pd(mat.m_matrix[0][3]);

    // output00 and output01.
    __m128d accumulator = _mm_mul_pd(matrixBlockA, otherMatrixFirstParam);
    __m128d temp1 = _mm_mul_pd(matrixBlockC, otherMatrixSecondParam);
    __m128d temp2 = _mm_mul_pd(matrixBlockE, otherMatrixThirdParam);
    __m128d temp3 = _mm_mul_pd(matrixBlockG, otherMatrixFourthParam);

    __m128d matrixBlockB = _mm_load_pd(&(m_matrix[0][2]));
    __m128d matrixBlockD = _mm_load_pd(&(m_matrix[1][2]));
    __m128d matrixBlockF = _mm_load_pd(&(m_matrix[2][2]));
    __m128d matrixBlockH = _mm_load_pd(&(m_matrix[3][2]));

    accumulator = _mm_add_pd(accumulator, temp1);
    accumulator = _mm_add_pd(accumulator, temp2);
    accumulator = _mm_add_pd(accumulator, temp3);
    _mm_store_pd(&m_matrix[0][0], accumulator);

    // output02 and output03.
    accumulator = _mm_mul_pd(matrixBlockB, otherMatrixFirstParam);
    temp1 = _mm_mul_pd(matrixBlockD, otherMatrixSecondParam);
    temp2 = _mm_mul_pd(matrixBlockF, otherMatrixThirdParam);
    temp3 = _mm_mul_pd(matrixBlockH, otherMatrixFourthParam);

    accumulator = _mm_add_pd(accumulator, temp1);
    accumulator = _mm_add_pd(accumulator, temp2);
    accumulator = _mm_add_pd(accumulator, temp3);
    _mm_store_pd(&m_matrix[0][2], accumulator);

    // Second row.
    otherMatrixFirstParam = _mm_set1_pd(mat.m_matrix[1][0]);
    otherMatrixSecondParam = _mm_set1_pd(mat.m_matrix[1][1]);
    otherMatrixThirdParam = _mm_set1_pd(mat.m_matrix[1][2]);
    otherMatrixFourthParam = _mm_set1_pd(mat.m_matrix[1][3]);

    // output10 and output11.
    accumulator = _mm_mul_pd(matrixBlockA, otherMatrixFirstParam);
    temp1 = _mm_mul_pd(matrixBlockC, otherMatrixSecondParam);
    temp2 = _mm_mul_pd(matrixBlockE, otherMatrixThirdParam);
    temp3 = _mm_mul_pd(matrixBlockG, otherMatrixFourthParam);

    accumulator = _mm_add_pd(accumulator, temp1);
    accumulator = _mm_add_pd(accumulator, temp2);
    accumulator = _mm_add_pd(accumulator, temp3);
    _mm_store_pd(&m_matrix[1][0], accumulator);

    // output12 and output13.
    accumulator = _mm_mul_pd(matrixBlockB, otherMatrixFirstParam);
    temp1 = _mm_mul_pd(matrixBlockD, otherMatrixSecondParam);
    temp2 = _mm_mul_pd(matrixBlockF, otherMatrixThirdParam);
    temp3 = _mm_mul_pd(matrixBlockH, otherMatrixFourthParam);

    accumulator = _mm_add_pd(accumulator, temp1);
    accumulator = _mm_add_pd(accumulator, temp2);
    accumulator = _mm_add_pd(accumulator, temp3);
    _mm_store_pd(&m_matrix[1][2], accumulator);

    // Third row.
    otherMatrixFirstParam = _mm_set1_pd(mat.m_matrix[2][0]);
    otherMatrixSecondParam = _mm_set1_pd(mat.m_matrix[2][1]);
    otherMatrixThirdParam = _mm_set1_pd(mat.m_matrix[2][2]);
    otherMatrixFourthParam = _mm_set1_pd(mat.m_matrix[2][3]);

    // output20 and output21.
    accumulator = _mm_mul_pd(matrixBlockA, otherMatrixFirstParam);
    temp1 = _mm_mul_pd(matrixBlockC, otherMatrixSecondParam);
    temp2 = _mm_mul_pd(matrixBlockE, otherMatrixThirdParam);
    temp3 = _mm_mul_pd(matrixBlockG, otherMatrixFourthParam);

    accumulator = _mm_add_pd(accumulator, temp1);
    accumulator = _mm_add_pd(accumulator, temp2);
    accumulator = _mm_add_pd(accumulator, temp3);
    _mm_store_pd(&m_matrix[2][0], accumulator);

    // output22 and output23.
    accumulator = _mm_mul_pd(matrixBlockB, otherMatrixFirstParam);
    temp1 = _mm_mul_pd(matrixBlockD, otherMatrixSecondParam);
    temp2 = _mm_mul_pd(matrixBlockF, otherMatrixThirdParam);
    temp3 = _mm_mul_pd(matrixBlockH, otherMatrixFourthParam);

    accumulator = _mm_add_pd(accumulator, temp1);
    accumulator = _mm_add_pd(accumulator, temp2);
    accumulator = _mm_add_pd(accumulator, temp3);
    _mm_store_pd(&m_matrix[2][2], accumulator);

    // Fourth row.
    otherMatrixFirstParam = _mm_set1_pd(mat.m_matrix[3][0]);
    otherMatrixSecondParam = _mm_set1_pd(mat.m_matrix[3][1]);
    otherMatrixThirdParam = _mm_set1_pd(mat.m_matrix[3][2]);
    otherMatrixFourthParam = _mm_set1_pd(mat.m_matrix[3][3]);

    // output30 and output31.
    accumulator = _mm_mul_pd(matrixBlockA, otherMatrixFirstParam);
    temp1 = _mm_mul_pd(matrixBlockC, otherMatrixSecondParam);
    temp2 = _mm_mul_pd(matrixBlockE, otherMatrixThirdParam);
    temp3 = _mm_mul_pd(matrixBlockG, otherMatrixFourthParam);

    accumulator = _mm_add_pd(accumulator, temp1);
    accumulator = _mm_add_pd(accumulator, temp2);
    accumulator = _mm_add_pd(accumulator, temp3);
    _mm_store_pd(&m_matrix[3][0], accumulator);

    // output32 and output33.
    accumulator = _mm_mul_pd(matrixBlockB, otherMatrixFirstParam);
    temp1 = _mm_mul_pd(matrixBlockD, otherMatrixSecondParam);
    temp2 = _mm_mul_pd(matrixBlockF, otherMatrixThirdParam);
    temp3 = _mm_mul_pd(matrixBlockH, otherMatrixFourthParam);

    accumulator = _mm_add_pd(accumulator, temp1);
    accumulator = _mm_add_pd(accumulator, temp2);
    accumulator = _mm_add_pd(accumulator, temp3);
    _mm_store_pd(&m_matrix[3][2], accumulator);
#else
    Matrix4 tmp;

    tmp[0][0] = (mat.m_matrix[0][0] * m_matrix[0][0] + mat.m_matrix[0][1] * m_matrix[1][0] + mat.m_matrix[0][2] * m_matrix[2][0] + mat.m_matrix[0][3] * m_matrix[3][0]);
    tmp[0][1] = (mat.m_matrix[0][0] * m_matrix[0][1] + mat.m_matrix[0][1] * m_matrix[1][1] + mat.m_matrix[0][2] * m_matrix[2][1] + mat.m_matrix[0][3] * m_matrix[3][1]);
    tmp[0][2] = (mat.m_matrix[0][0] * m_matrix[0][2] + mat.m_matrix[0][1] * m_matrix[1][2] + mat.m_matrix[0][2] * m_matrix[2][2] + mat.m_matrix[0][3] * m_matrix[3][2]);
    tmp[0][3] = (mat.m_matrix[0][0] * m_matrix[0][3] + mat.m_matrix[0][1] * m_matrix[1][3] + mat.m_matrix[0][2] * m_matrix[2][3] + mat.m_matrix[0][3] * m_matrix[3][3]);

    tmp[1][0] = (mat.m_matrix[1][0] * m_matrix[0][0] + mat.m_matrix[1][1] * m_matrix[1][0] + mat.m_matrix[1][2] * m_matrix[2][0] + mat.m_matrix[1][3] * m_matrix[3][0]);
    tmp[1][1] = (mat.m_matrix[1][0] * m_matrix[0][1] + mat.m_matrix[1][1] * m_matrix[1][1] + mat.m_matrix[1][2] * m_matrix[2][1] + mat.m_matrix[1][3] * m_matrix[3][1]);
    tmp[1][2] = (mat.m_matrix[1][0] * m_matrix[0][2] + mat.m_matrix[1][1] * m_matrix[1][2] + mat.m_matrix[1][2] * m_matrix[2][2] + mat.m_matrix[1][3] * m_matrix[3][2]);
    tmp[1][3] = (mat.m_matrix[1][0] * m_matrix[0][3] + mat.m_matrix[1][1] * m_matrix[1][3] + mat.m_matrix[1][2] * m_matrix[2][3] + mat.m_matrix[1][3] * m_matrix[3][3]);

    tmp[2][0] = (mat.m_matrix[2][0] * m_matrix[0][0] + mat.m_matrix[2][1] * m_matrix[1][0] + mat.m_matrix[2][2] * m_matrix[2][0] + mat.m_matrix[2][3] * m_matrix[3][0]);
    tmp[2][1] = (mat.m_matrix[2][0] * m_matrix[0][1] + mat.m_matrix[2][1] * m_matrix[1][1] + mat.m_matrix[2][2] * m_matrix[2][1] + mat.m_matrix[2][3] * m_matrix[3][1]);
    tmp[2][2] = (mat.m_matrix[2][0] * m_matrix[0][2] + mat.m_matrix[2][1] * m_matrix[1][2] + mat.m_matrix[2][2] * m_matrix[2][2] + mat.m_matrix[2][3] * m_matrix[3][2]);
    tmp[2][3] = (mat.m_matrix[2][0] * m_matrix[0][3] + mat.m_matrix[2][1] * m_matrix[1][3] + mat.m_matrix[2][2] * m_matrix[2][3] + mat.m_matrix[2][3] * m_matrix[3][3]);

    tmp[3][0] = (mat.m_matrix[3][0] * m_matrix[0][0] + mat.m_matrix[3][1] * m_matrix[1][0] + mat.m_matrix[3][2] * m_matrix[2][0] + mat.m_matrix[3][3] * m_matrix[3][0]);
    tmp[3][1] = (mat.m_matrix[3][0] * m_matrix[0][1] + mat.m_matrix[3][1] * m_matrix[1][1] + mat.m_matrix[3][2] * m_matrix[2][1] + mat.m_matrix[3][3] * m_matrix[3][1]);
    tmp[3][2] = (mat.m_matrix[3][0] * m_matrix[0][2] + mat.m_matrix[3][1] * m_matrix[1][2] + mat.m_matrix[3][2] * m_matrix[2][2] + mat.m_matrix[3][3] * m_matrix[3][2]);
    tmp[3][3] = (mat.m_matrix[3][0] * m_matrix[0][3] + mat.m_matrix[3][1] * m_matrix[1][3] + mat.m_matrix[3][2] * m_matrix[2][3] + mat.m_matrix[3][3] * m_matrix[3][3]);

    setMatrix(tmp);
#endif
    return *this;
}

void TransformationMatrix::multVecMatrix(double x,
    double y,
    double& resultX,
    double& resultY) const
{
    resultX = m_matrix[3][0] + x * m_matrix[0][0] + y * m_matrix[1][0];
    resultY = m_matrix[3][1] + x * m_matrix[0][1] + y * m_matrix[1][1];
    double w = m_matrix[3][3] + x * m_matrix[0][3] + y * m_matrix[1][3];
    if (w != 1 && w != 0) {
        resultX /= w;
        resultY /= w;
    }
}

void TransformationMatrix::multVecMatrix(double x,
    double y,
    double z,
    double& resultX,
    double& resultY,
    double& resultZ) const
{
    resultX = m_matrix[3][0] + x * m_matrix[0][0] + y * m_matrix[1][0] + z * m_matrix[2][0];
    resultY = m_matrix[3][1] + x * m_matrix[0][1] + y * m_matrix[1][1] + z * m_matrix[2][1];
    resultZ = m_matrix[3][2] + x * m_matrix[0][2] + y * m_matrix[1][2] + z * m_matrix[2][2];
    double w = m_matrix[3][3] + x * m_matrix[0][3] + y * m_matrix[1][3] + z * m_matrix[2][3];
    if (w != 1 && w != 0) {
        resultX /= w;
        resultY /= w;
        resultZ /= w;
    }
}

bool TransformationMatrix::isInvertible() const
{
    if (isIdentityOrTranslation())
        return true;

    double det = blink::determinant4x4(m_matrix);

    if (fabs(det) < SmallNumber)
        return false;

    return true;
}

TransformationMatrix TransformationMatrix::inverse() const
{
    if (isIdentityOrTranslation()) {
        // identity matrix
        if (m_matrix[3][0] == 0 && m_matrix[3][1] == 0 && m_matrix[3][2] == 0)
            return TransformationMatrix();

        // translation
        return TransformationMatrix(1, 0, 0, 0, 0, 1, 0, 0, 0, 0, 1, 0,
            -m_matrix[3][0], -m_matrix[3][1],
            -m_matrix[3][2], 1);
    }

    TransformationMatrix invMat;
    bool inverted = blink::inverse(m_matrix, invMat.m_matrix);
    if (!inverted)
        return TransformationMatrix();

    return invMat;
}

void TransformationMatrix::makeAffine()
{
    m_matrix[0][2] = 0;
    m_matrix[0][3] = 0;

    m_matrix[1][2] = 0;
    m_matrix[1][3] = 0;

    m_matrix[2][0] = 0;
    m_matrix[2][1] = 0;
    m_matrix[2][2] = 1;
    m_matrix[2][3] = 0;

    m_matrix[3][2] = 0;
    m_matrix[3][3] = 1;
}

AffineTransform TransformationMatrix::toAffineTransform() const
{
    return AffineTransform(m_matrix[0][0], m_matrix[0][1], m_matrix[1][0],
        m_matrix[1][1], m_matrix[3][0], m_matrix[3][1]);
}

void TransformationMatrix::flattenTo2d()
{
    m_matrix[2][0] = 0;
    m_matrix[2][1] = 0;
    m_matrix[0][2] = 0;
    m_matrix[1][2] = 0;
    m_matrix[2][2] = 1;
    m_matrix[3][2] = 0;
    m_matrix[2][3] = 0;
}

static inline void blendFloat(double& from, double to, double progress)
{
    if (from != to)
        from = from + (to - from) * progress;
}

void TransformationMatrix::blend(const TransformationMatrix& from,
    double progress)
{
    if (from.isIdentity() && isIdentity())
        return;

    // decompose
    DecomposedType fromDecomp;
    DecomposedType toDecomp;
    if (!from.decompose(fromDecomp) || !decompose(toDecomp)) {
        if (progress < 0.5)
            *this = from;
        return;
    }

    // interpolate
    blendFloat(fromDecomp.scaleX, toDecomp.scaleX, progress);
    blendFloat(fromDecomp.scaleY, toDecomp.scaleY, progress);
    blendFloat(fromDecomp.scaleZ, toDecomp.scaleZ, progress);
    blendFloat(fromDecomp.skewXY, toDecomp.skewXY, progress);
    blendFloat(fromDecomp.skewXZ, toDecomp.skewXZ, progress);
    blendFloat(fromDecomp.skewYZ, toDecomp.skewYZ, progress);
    blendFloat(fromDecomp.translateX, toDecomp.translateX, progress);
    blendFloat(fromDecomp.translateY, toDecomp.translateY, progress);
    blendFloat(fromDecomp.translateZ, toDecomp.translateZ, progress);
    blendFloat(fromDecomp.perspectiveX, toDecomp.perspectiveX, progress);
    blendFloat(fromDecomp.perspectiveY, toDecomp.perspectiveY, progress);
    blendFloat(fromDecomp.perspectiveZ, toDecomp.perspectiveZ, progress);
    blendFloat(fromDecomp.perspectiveW, toDecomp.perspectiveW, progress);

    slerp(&fromDecomp.quaternionX, &toDecomp.quaternionX, progress);

    // recompose
    recompose(fromDecomp);
}

bool TransformationMatrix::decompose(DecomposedType& decomp) const
{
    if (isIdentity()) {
        memset(&decomp, 0, sizeof(decomp));
        decomp.perspectiveW = 1;
        decomp.scaleX = 1;
        decomp.scaleY = 1;
        decomp.scaleZ = 1;
    }

    if (!blink::decompose(m_matrix, decomp))
        return false;
    return true;
}

void TransformationMatrix::recompose(const DecomposedType& decomp)
{
    makeIdentity();

    // first apply perspective
    m_matrix[0][3] = decomp.perspectiveX;
    m_matrix[1][3] = decomp.perspectiveY;
    m_matrix[2][3] = decomp.perspectiveZ;
    m_matrix[3][3] = decomp.perspectiveW;

    // now translate
    translate3d(decomp.translateX, decomp.translateY, decomp.translateZ);

    // apply rotation
    double xx = decomp.quaternionX * decomp.quaternionX;
    double xy = decomp.quaternionX * decomp.quaternionY;
    double xz = decomp.quaternionX * decomp.quaternionZ;
    double xw = decomp.quaternionX * decomp.quaternionW;
    double yy = decomp.quaternionY * decomp.quaternionY;
    double yz = decomp.quaternionY * decomp.quaternionZ;
    double yw = decomp.quaternionY * decomp.quaternionW;
    double zz = decomp.quaternionZ * decomp.quaternionZ;
    double zw = decomp.quaternionZ * decomp.quaternionW;

    // Construct a composite rotation matrix from the quaternion values
    TransformationMatrix rotationMatrix(
        1 - 2 * (yy + zz), 2 * (xy - zw), 2 * (xz + yw), 0, 2 * (xy + zw),
        1 - 2 * (xx + zz), 2 * (yz - xw), 0, 2 * (xz - yw), 2 * (yz + xw),
        1 - 2 * (xx + yy), 0, 0, 0, 0, 1);

    multiply(rotationMatrix);

    // now apply skew
    if (decomp.skewYZ) {
        TransformationMatrix tmp;
        tmp.setM32(decomp.skewYZ);
        multiply(tmp);
    }

    if (decomp.skewXZ) {
        TransformationMatrix tmp;
        tmp.setM31(decomp.skewXZ);
        multiply(tmp);
    }

    if (decomp.skewXY) {
        TransformationMatrix tmp;
        tmp.setM21(decomp.skewXY);
        multiply(tmp);
    }

    // finally, apply scale
    scale3d(decomp.scaleX, decomp.scaleY, decomp.scaleZ);
}

bool TransformationMatrix::isIntegerTranslation() const
{
    if (!isIdentityOrTranslation())
        return false;

    // Check for translate Z.
    if (m_matrix[3][2])
        return false;

    // Check for non-integer translate X/Y.
    if (static_cast<int>(m_matrix[3][0]) != m_matrix[3][0] || static_cast<int>(m_matrix[3][1]) != m_matrix[3][1])
        return false;

    return true;
}

FloatSize TransformationMatrix::to2DTranslation() const
{
    ASSERT(isIdentityOr2DTranslation());
    return FloatSize(m_matrix[3][0], m_matrix[3][1]);
}

void TransformationMatrix::toColumnMajorFloatArray(FloatMatrix4& result) const
{
    result[0] = m11();
    result[1] = m12();
    result[2] = m13();
    result[3] = m14();
    result[4] = m21();
    result[5] = m22();
    result[6] = m23();
    result[7] = m24();
    result[8] = m31();
    result[9] = m32();
    result[10] = m33();
    result[11] = m34();
    result[12] = m41();
    result[13] = m42();
    result[14] = m43();
    result[15] = m44();
}

SkMatrix44 TransformationMatrix::toSkMatrix44(
    const TransformationMatrix& matrix)
{
    SkMatrix44 ret(SkMatrix44::kUninitialized_Constructor);
    ret.setDouble(0, 0, matrix.m11());
    ret.setDouble(0, 1, matrix.m21());
    ret.setDouble(0, 2, matrix.m31());
    ret.setDouble(0, 3, matrix.m41());
    ret.setDouble(1, 0, matrix.m12());
    ret.setDouble(1, 1, matrix.m22());
    ret.setDouble(1, 2, matrix.m32());
    ret.setDouble(1, 3, matrix.m42());
    ret.setDouble(2, 0, matrix.m13());
    ret.setDouble(2, 1, matrix.m23());
    ret.setDouble(2, 2, matrix.m33());
    ret.setDouble(2, 3, matrix.m43());
    ret.setDouble(3, 0, matrix.m14());
    ret.setDouble(3, 1, matrix.m24());
    ret.setDouble(3, 2, matrix.m34());
    ret.setDouble(3, 3, matrix.m44());
    return ret;
}

String TransformationMatrix::toString(bool asMatrix) const
{
    if (asMatrix) {
        // Return as a matrix in row-major order.
        return String::format(
            "[%lg,%lg,%lg,%lg,\n%lg,%lg,%lg,%lg,\n%lg,%lg,%lg,%lg,\n%lg,%lg,%lg,%"
            "lg]",
            m11(), m21(), m31(), m41(), m12(), m22(), m32(), m42(), m13(), m23(),
            m33(), m43(), m14(), m24(), m34(), m44());
    }

    TransformationMatrix::DecomposedType decomposition;
    if (!decompose(decomposition))
        return toString(true) + " (degenerate)";

    if (isIdentityOrTranslation()) {
        if (decomposition.translateX == 0 && decomposition.translateY == 0 && decomposition.translateZ == 0)
            return "identity";
        return String::format("translation(%lg,%lg,%lg)", decomposition.translateX,
            decomposition.translateY, decomposition.translateZ);
    }

    return String::format(
        "translation(%lg,%lg,%lg), scale(%lg,%lg,%lg), skew(%lg,%lg,%lg), "
        "quaternion(%lg,%lg,%lg,%lg), perspective(%lg,%lg,%lg,%lg)",
        decomposition.translateX, decomposition.translateY,
        decomposition.translateZ, decomposition.scaleX, decomposition.scaleY,
        decomposition.scaleZ, decomposition.skewXY, decomposition.skewXZ,
        decomposition.skewYZ, decomposition.quaternionX,
        decomposition.quaternionY, decomposition.quaternionZ,
        decomposition.quaternionW, decomposition.perspectiveX,
        decomposition.perspectiveY, decomposition.perspectiveZ,
        decomposition.perspectiveW);
}

} // namespace blink
