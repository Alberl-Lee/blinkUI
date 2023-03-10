// Copyright 2013 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "ui/base/ime/win/imm32_manager.h"

#include "testing/gtest/include/gtest/gtest.h"

namespace ui {
namespace {

    struct InputModeTestCase {
        TextInputMode input_mode;
        DWORD conversion_mode;
        BOOL expected_open;
        DWORD expected_conversion_mode;
    };

    // Google Test pretty-printer.
    void PrintTo(const InputModeTestCase& data, std::ostream* os)
    {
        *os << " input_mode: " << testing::PrintToString(data.input_mode)
            << "; conversion_mode: " << testing::PrintToString(data.conversion_mode);
    }

    class IMM32ManagerTest
        : public ::testing::TestWithParam<InputModeTestCase> {
    };

    const InputModeTestCase
        kInputModeTestCases[]
        = {
              { TEXT_INPUT_MODE_DEFAULT, 0, FALSE, 0 },
              { TEXT_INPUT_MODE_DEFAULT, IME_CMODE_NATIVE, FALSE, IME_CMODE_NATIVE },
              { TEXT_INPUT_MODE_VERBATIM, 0, FALSE, 0 },
              { TEXT_INPUT_MODE_VERBATIM, IME_CMODE_KATAKANA, FALSE, IME_CMODE_KATAKANA },
              { TEXT_INPUT_MODE_LATIN, 0, FALSE, 0 },
              { TEXT_INPUT_MODE_LATIN, IME_CMODE_NATIVE, FALSE, IME_CMODE_NATIVE },
              { TEXT_INPUT_MODE_LATIN_NAME, 0, FALSE, 0 },
              { TEXT_INPUT_MODE_LATIN_NAME, IME_CMODE_NATIVE, FALSE, IME_CMODE_NATIVE },
              { TEXT_INPUT_MODE_LATIN_PROSE, 0, FALSE, 0 },
              { TEXT_INPUT_MODE_LATIN_PROSE, IME_CMODE_NATIVE, FALSE, IME_CMODE_NATIVE },
              { TEXT_INPUT_MODE_FULL_WIDTH_LATIN,
                  IME_CMODE_NATIVE | IME_CMODE_KATAKANA | IME_CMODE_FULLSHAPE,
                  TRUE,
                  IME_CMODE_FULLSHAPE },
              { TEXT_INPUT_MODE_KANA,
                  0,
                  TRUE,
                  IME_CMODE_NATIVE | IME_CMODE_FULLSHAPE },
              { TEXT_INPUT_MODE_KANA,
                  IME_CMODE_ROMAN,
                  TRUE,
                  IME_CMODE_NATIVE | IME_CMODE_FULLSHAPE | IME_CMODE_ROMAN },
              { TEXT_INPUT_MODE_KATAKANA,
                  IME_CMODE_NATIVE | IME_CMODE_FULLSHAPE,
                  TRUE,
                  IME_CMODE_NATIVE | IME_CMODE_KATAKANA | IME_CMODE_FULLSHAPE },
              { TEXT_INPUT_MODE_KATAKANA,
                  IME_CMODE_NATIVE | IME_CMODE_FULLSHAPE | IME_CMODE_ROMAN,
                  TRUE,
                  IME_CMODE_NATIVE | IME_CMODE_KATAKANA | IME_CMODE_FULLSHAPE
                      | IME_CMODE_ROMAN },
              { TEXT_INPUT_MODE_NUMERIC, 0, FALSE, 0 },
              { TEXT_INPUT_MODE_NUMERIC, IME_CMODE_FULLSHAPE, FALSE, IME_CMODE_FULLSHAPE },
              { TEXT_INPUT_MODE_TEL, 0, FALSE, 0 },
              { TEXT_INPUT_MODE_TEL, IME_CMODE_ROMAN, FALSE, IME_CMODE_ROMAN },
              { TEXT_INPUT_MODE_EMAIL, 0, FALSE, 0 },
              { TEXT_INPUT_MODE_EMAIL, IME_CMODE_CHARCODE, FALSE, IME_CMODE_CHARCODE },
              { TEXT_INPUT_MODE_URL, 0, FALSE, 0 },
              { TEXT_INPUT_MODE_URL, IME_CMODE_HANJACONVERT, FALSE, IME_CMODE_HANJACONVERT },
          };

    TEST_P(IMM32ManagerTest, ConvertInputModeToImmFlags)
    {
        const InputModeTestCase& test_case = GetParam();

        BOOL open;
        DWORD conversion_mode;
        // Call testee method.
        IMM32Manager::ConvertInputModeToImmFlags(test_case.input_mode,
            test_case.conversion_mode,
            &open,
            &conversion_mode);

        EXPECT_EQ(test_case.expected_open, open);
        EXPECT_EQ(test_case.expected_conversion_mode, conversion_mode);
    }

    INSTANTIATE_TEST_CASE_P(,
        IMM32ManagerTest,
        ::testing::ValuesIn(kInputModeTestCases));

} // namespace
} // namespace ui
