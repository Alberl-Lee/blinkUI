// Copyright 2008-2009 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "src/regexp/regexp-macro-assembler-irregexp.h"

#include "src/ast/ast.h"
#include "src/objects-inl.h"
#include "src/regexp/bytecodes-irregexp.h"
#include "src/regexp/regexp-macro-assembler-irregexp-inl.h"
#include "src/regexp/regexp-macro-assembler.h"

namespace v8 {
namespace internal {

    RegExpMacroAssemblerIrregexp::RegExpMacroAssemblerIrregexp(Isolate* isolate,
        Zone* zone)
        : RegExpMacroAssembler(isolate, zone)
        , buffer_(Vector<byte>::New(1024))
        , pc_(0)
        , own_buffer_(true)
        , advance_current_end_(kInvalidPC)
        , isolate_(isolate)
    {
    }

    RegExpMacroAssemblerIrregexp::~RegExpMacroAssemblerIrregexp()
    {
        if (backtrack_.is_linked())
            backtrack_.Unuse();
        if (own_buffer_)
            buffer_.Dispose();
    }

    RegExpMacroAssemblerIrregexp::IrregexpImplementation
    RegExpMacroAssemblerIrregexp::Implementation()
    {
        return kBytecodeImplementation;
    }

    void RegExpMacroAssemblerIrregexp::Bind(Label* l)
    {
        advance_current_end_ = kInvalidPC;
        DCHECK(!l->is_bound());
        if (l->is_linked()) {
            int pos = l->pos();
            while (pos != 0) {
                int fixup = pos;
                pos = *reinterpret_cast<int32_t*>(buffer_.start() + fixup);
                *reinterpret_cast<uint32_t*>(buffer_.start() + fixup) = pc_;
            }
        }
        l->bind_to(pc_);
    }

    void RegExpMacroAssemblerIrregexp::EmitOrLink(Label* l)
    {
        if (l == nullptr)
            l = &backtrack_;
        if (l->is_bound()) {
            Emit32(l->pos());
        } else {
            int pos = 0;
            if (l->is_linked()) {
                pos = l->pos();
            }
            l->link_to(pc_);
            Emit32(pos);
        }
    }

    void RegExpMacroAssemblerIrregexp::PopRegister(int register_index)
    {
        DCHECK_LE(0, register_index);
        DCHECK_GE(kMaxRegister, register_index);
        Emit(BC_POP_REGISTER, register_index);
    }

    void RegExpMacroAssemblerIrregexp::PushRegister(
        int register_index,
        StackCheckFlag check_stack_limit)
    {
        DCHECK_LE(0, register_index);
        DCHECK_GE(kMaxRegister, register_index);
        Emit(BC_PUSH_REGISTER, register_index);
    }

    void RegExpMacroAssemblerIrregexp::WriteCurrentPositionToRegister(
        int register_index, int cp_offset)
    {
        DCHECK_LE(0, register_index);
        DCHECK_GE(kMaxRegister, register_index);
        Emit(BC_SET_REGISTER_TO_CP, register_index);
        Emit32(cp_offset); // Current position offset.
    }

    void RegExpMacroAssemblerIrregexp::ClearRegisters(int reg_from, int reg_to)
    {
        DCHECK(reg_from <= reg_to);
        for (int reg = reg_from; reg <= reg_to; reg++) {
            SetRegister(reg, -1);
        }
    }

    void RegExpMacroAssemblerIrregexp::ReadCurrentPositionFromRegister(
        int register_index)
    {
        DCHECK_LE(0, register_index);
        DCHECK_GE(kMaxRegister, register_index);
        Emit(BC_SET_CP_TO_REGISTER, register_index);
    }

    void RegExpMacroAssemblerIrregexp::WriteStackPointerToRegister(
        int register_index)
    {
        DCHECK_LE(0, register_index);
        DCHECK_GE(kMaxRegister, register_index);
        Emit(BC_SET_REGISTER_TO_SP, register_index);
    }

    void RegExpMacroAssemblerIrregexp::ReadStackPointerFromRegister(
        int register_index)
    {
        DCHECK_LE(0, register_index);
        DCHECK_GE(kMaxRegister, register_index);
        Emit(BC_SET_SP_TO_REGISTER, register_index);
    }

    void RegExpMacroAssemblerIrregexp::SetCurrentPositionFromEnd(int by)
    {
        DCHECK(is_uint24(by));
        Emit(BC_SET_CURRENT_POSITION_FROM_END, by);
    }

    void RegExpMacroAssemblerIrregexp::SetRegister(int register_index, int to)
    {
        DCHECK_LE(0, register_index);
        DCHECK_GE(kMaxRegister, register_index);
        Emit(BC_SET_REGISTER, register_index);
        Emit32(to);
    }

    void RegExpMacroAssemblerIrregexp::AdvanceRegister(int register_index, int by)
    {
        DCHECK_LE(0, register_index);
        DCHECK_GE(kMaxRegister, register_index);
        Emit(BC_ADVANCE_REGISTER, register_index);
        Emit32(by);
    }

    void RegExpMacroAssemblerIrregexp::PopCurrentPosition()
    {
        Emit(BC_POP_CP, 0);
    }

    void RegExpMacroAssemblerIrregexp::PushCurrentPosition()
    {
        Emit(BC_PUSH_CP, 0);
    }

    void RegExpMacroAssemblerIrregexp::Backtrack()
    {
        Emit(BC_POP_BT, 0);
    }

    void RegExpMacroAssemblerIrregexp::GoTo(Label* l)
    {
        if (advance_current_end_ == pc_) {
            // Combine advance current and goto.
            pc_ = advance_current_start_;
            Emit(BC_ADVANCE_CP_AND_GOTO, advance_current_offset_);
            EmitOrLink(l);
            advance_current_end_ = kInvalidPC;
        } else {
            // Regular goto.
            Emit(BC_GOTO, 0);
            EmitOrLink(l);
        }
    }

    void RegExpMacroAssemblerIrregexp::PushBacktrack(Label* l)
    {
        Emit(BC_PUSH_BT, 0);
        EmitOrLink(l);
    }

    bool RegExpMacroAssemblerIrregexp::Succeed()
    {
        Emit(BC_SUCCEED, 0);
        return false; // Restart matching for global regexp not supported.
    }

    void RegExpMacroAssemblerIrregexp::Fail()
    {
        Emit(BC_FAIL, 0);
    }

    void RegExpMacroAssemblerIrregexp::AdvanceCurrentPosition(int by)
    {
        DCHECK_LE(kMinCPOffset, by);
        DCHECK_GE(kMaxCPOffset, by);
        advance_current_start_ = pc_;
        advance_current_offset_ = by;
        Emit(BC_ADVANCE_CP, by);
        advance_current_end_ = pc_;
    }

    void RegExpMacroAssemblerIrregexp::CheckGreedyLoop(
        Label* on_tos_equals_current_position)
    {
        Emit(BC_CHECK_GREEDY, 0);
        EmitOrLink(on_tos_equals_current_position);
    }

    void RegExpMacroAssemblerIrregexp::LoadCurrentCharacter(int cp_offset,
        Label* on_failure,
        bool check_bounds,
        int characters)
    {
        DCHECK_LE(kMinCPOffset, cp_offset);
        DCHECK_GE(kMaxCPOffset, cp_offset);
        int bytecode;
        if (check_bounds) {
            if (characters == 4) {
                bytecode = BC_LOAD_4_CURRENT_CHARS;
            } else if (characters == 2) {
                bytecode = BC_LOAD_2_CURRENT_CHARS;
            } else {
                DCHECK_EQ(1, characters);
                bytecode = BC_LOAD_CURRENT_CHAR;
            }
        } else {
            if (characters == 4) {
                bytecode = BC_LOAD_4_CURRENT_CHARS_UNCHECKED;
            } else if (characters == 2) {
                bytecode = BC_LOAD_2_CURRENT_CHARS_UNCHECKED;
            } else {
                DCHECK_EQ(1, characters);
                bytecode = BC_LOAD_CURRENT_CHAR_UNCHECKED;
            }
        }
        Emit(bytecode, cp_offset);
        if (check_bounds)
            EmitOrLink(on_failure);
    }

    void RegExpMacroAssemblerIrregexp::CheckCharacterLT(uc16 limit,
        Label* on_less)
    {
        Emit(BC_CHECK_LT, limit);
        EmitOrLink(on_less);
    }

    void RegExpMacroAssemblerIrregexp::CheckCharacterGT(uc16 limit,
        Label* on_greater)
    {
        Emit(BC_CHECK_GT, limit);
        EmitOrLink(on_greater);
    }

    void RegExpMacroAssemblerIrregexp::CheckCharacter(uint32_t c, Label* on_equal)
    {
        if (c > MAX_FIRST_ARG) {
            Emit(BC_CHECK_4_CHARS, 0);
            Emit32(c);
        } else {
            Emit(BC_CHECK_CHAR, c);
        }
        EmitOrLink(on_equal);
    }

    void RegExpMacroAssemblerIrregexp::CheckAtStart(Label* on_at_start)
    {
        Emit(BC_CHECK_AT_START, 0);
        EmitOrLink(on_at_start);
    }

    void RegExpMacroAssemblerIrregexp::CheckNotAtStart(int cp_offset,
        Label* on_not_at_start)
    {
        Emit(BC_CHECK_NOT_AT_START, cp_offset);
        EmitOrLink(on_not_at_start);
    }

    void RegExpMacroAssemblerIrregexp::CheckNotCharacter(uint32_t c,
        Label* on_not_equal)
    {
        if (c > MAX_FIRST_ARG) {
            Emit(BC_CHECK_NOT_4_CHARS, 0);
            Emit32(c);
        } else {
            Emit(BC_CHECK_NOT_CHAR, c);
        }
        EmitOrLink(on_not_equal);
    }

    void RegExpMacroAssemblerIrregexp::CheckCharacterAfterAnd(
        uint32_t c,
        uint32_t mask,
        Label* on_equal)
    {
        if (c > MAX_FIRST_ARG) {
            Emit(BC_AND_CHECK_4_CHARS, 0);
            Emit32(c);
        } else {
            Emit(BC_AND_CHECK_CHAR, c);
        }
        Emit32(mask);
        EmitOrLink(on_equal);
    }

    void RegExpMacroAssemblerIrregexp::CheckNotCharacterAfterAnd(
        uint32_t c,
        uint32_t mask,
        Label* on_not_equal)
    {
        if (c > MAX_FIRST_ARG) {
            Emit(BC_AND_CHECK_NOT_4_CHARS, 0);
            Emit32(c);
        } else {
            Emit(BC_AND_CHECK_NOT_CHAR, c);
        }
        Emit32(mask);
        EmitOrLink(on_not_equal);
    }

    void RegExpMacroAssemblerIrregexp::CheckNotCharacterAfterMinusAnd(
        uc16 c,
        uc16 minus,
        uc16 mask,
        Label* on_not_equal)
    {
        Emit(BC_MINUS_AND_CHECK_NOT_CHAR, c);
        Emit16(minus);
        Emit16(mask);
        EmitOrLink(on_not_equal);
    }

    void RegExpMacroAssemblerIrregexp::CheckCharacterInRange(
        uc16 from,
        uc16 to,
        Label* on_in_range)
    {
        Emit(BC_CHECK_CHAR_IN_RANGE, 0);
        Emit16(from);
        Emit16(to);
        EmitOrLink(on_in_range);
    }

    void RegExpMacroAssemblerIrregexp::CheckCharacterNotInRange(
        uc16 from,
        uc16 to,
        Label* on_not_in_range)
    {
        Emit(BC_CHECK_CHAR_NOT_IN_RANGE, 0);
        Emit16(from);
        Emit16(to);
        EmitOrLink(on_not_in_range);
    }

    void RegExpMacroAssemblerIrregexp::CheckBitInTable(
        Handle<ByteArray> table, Label* on_bit_set)
    {
        Emit(BC_CHECK_BIT_IN_TABLE, 0);
        EmitOrLink(on_bit_set);
        for (int i = 0; i < kTableSize; i += kBitsPerByte) {
            int byte = 0;
            for (int j = 0; j < kBitsPerByte; j++) {
                if (table->get(i + j) != 0)
                    byte |= 1 << j;
            }
            Emit8(byte);
        }
    }

    void RegExpMacroAssemblerIrregexp::CheckNotBackReference(int start_reg,
        bool read_backward,
        Label* on_not_equal)
    {
        DCHECK_LE(0, start_reg);
        DCHECK_GE(kMaxRegister, start_reg);
        Emit(read_backward ? BC_CHECK_NOT_BACK_REF_BACKWARD : BC_CHECK_NOT_BACK_REF,
            start_reg);
        EmitOrLink(on_not_equal);
    }

    void RegExpMacroAssemblerIrregexp::CheckNotBackReferenceIgnoreCase(
        int start_reg, bool read_backward, bool unicode, Label* on_not_equal)
    {
        DCHECK_LE(0, start_reg);
        DCHECK_GE(kMaxRegister, start_reg);
        Emit(read_backward ? (unicode ? BC_CHECK_NOT_BACK_REF_NO_CASE_UNICODE_BACKWARD
                                      : BC_CHECK_NOT_BACK_REF_NO_CASE_BACKWARD)
                           : (unicode ? BC_CHECK_NOT_BACK_REF_NO_CASE_UNICODE
                                      : BC_CHECK_NOT_BACK_REF_NO_CASE),
            start_reg);
        EmitOrLink(on_not_equal);
    }

    void RegExpMacroAssemblerIrregexp::IfRegisterLT(int register_index,
        int comparand,
        Label* on_less_than)
    {
        DCHECK_LE(0, register_index);
        DCHECK_GE(kMaxRegister, register_index);
        Emit(BC_CHECK_REGISTER_LT, register_index);
        Emit32(comparand);
        EmitOrLink(on_less_than);
    }

    void RegExpMacroAssemblerIrregexp::IfRegisterGE(int register_index,
        int comparand,
        Label* on_greater_or_equal)
    {
        DCHECK_LE(0, register_index);
        DCHECK_GE(kMaxRegister, register_index);
        Emit(BC_CHECK_REGISTER_GE, register_index);
        Emit32(comparand);
        EmitOrLink(on_greater_or_equal);
    }

    void RegExpMacroAssemblerIrregexp::IfRegisterEqPos(int register_index,
        Label* on_eq)
    {
        DCHECK_LE(0, register_index);
        DCHECK_GE(kMaxRegister, register_index);
        Emit(BC_CHECK_REGISTER_EQ_POS, register_index);
        EmitOrLink(on_eq);
    }

    Handle<HeapObject> RegExpMacroAssemblerIrregexp::GetCode(
        Handle<String> source)
    {
        Bind(&backtrack_);
        Emit(BC_POP_BT, 0);
        Handle<ByteArray> array = isolate_->factory()->NewByteArray(length());
        Copy(array->GetDataStartAddress());
        return array;
    }

    int RegExpMacroAssemblerIrregexp::length()
    {
        return pc_;
    }

    void RegExpMacroAssemblerIrregexp::Copy(byte* a)
    {
        MemCopy(a, buffer_.start(), length());
    }

    void RegExpMacroAssemblerIrregexp::Expand()
    {
        bool old_buffer_was_our_own = own_buffer_;
        Vector<byte> old_buffer = buffer_;
        buffer_ = Vector<byte>::New(old_buffer.length() * 2);
        own_buffer_ = true;
        MemCopy(buffer_.start(), old_buffer.start(), old_buffer.length());
        if (old_buffer_was_our_own) {
            old_buffer.Dispose();
        }
    }

} // namespace internal
} // namespace v8
