// Copyright 2014 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "wtf/typed_arrays/ArrayPiece.h"

#include "wtf/Assertions.h"
#include "wtf/typed_arrays/ArrayBuffer.h"
#include "wtf/typed_arrays/ArrayBufferView.h"

namespace WTF {

ArrayPiece::ArrayPiece()
{
    initNull();
}

ArrayPiece::ArrayPiece(void* data, unsigned byteLength)
{
    initWithData(data, byteLength);
}

ArrayPiece::ArrayPiece(ArrayBuffer* buffer)
{
    if (buffer) {
        initWithData(buffer->data(), buffer->byteLength());
    } else {
        initNull();
    }
}

ArrayPiece::ArrayPiece(ArrayBufferView* buffer)
{
    if (buffer) {
        initWithData(buffer->baseAddress(), buffer->byteLength());
    } else {
        initNull();
    }
}

bool ArrayPiece::isNull() const
{
    return m_isNull;
}

void* ArrayPiece::data() const
{
    DCHECK(!isNull());
    return m_data;
}

unsigned char* ArrayPiece::bytes() const
{
    return static_cast<unsigned char*>(data());
}

unsigned ArrayPiece::byteLength() const
{
    DCHECK(!isNull());
    return m_byteLength;
}

void ArrayPiece::initWithData(void* data, unsigned byteLength)
{
    m_byteLength = byteLength;
    m_data = data;
    m_isNull = false;
}

void ArrayPiece::initNull()
{
    m_byteLength = 0;
    m_data = 0;
    m_isNull = true;
}

} // namespace WTF
