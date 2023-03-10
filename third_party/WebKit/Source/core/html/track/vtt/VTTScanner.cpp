/*
 * Copyright (c) 2013, Opera Software ASA. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice, this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 * 3. Neither the name of Opera Software ASA nor the names of its
 *    contributors may be used to endorse or promote products derived
 *    from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE
 * COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#include "core/html/track/vtt/VTTScanner.h"

#include "wtf/text/StringToNumber.h"

namespace blink {

VTTScanner::VTTScanner(const String& line)
    : m_is8Bit(line.is8Bit())
{
    if (m_is8Bit) {
        m_data.characters8 = line.characters8();
        m_end.characters8 = m_data.characters8 + line.length();
    } else {
        m_data.characters16 = line.characters16();
        m_end.characters16 = m_data.characters16 + line.length();
    }
}

bool VTTScanner::scan(char c)
{
    if (!match(c))
        return false;
    advance();
    return true;
}

bool VTTScanner::scan(const LChar* characters, size_t charactersCount)
{
    unsigned matchLength = m_is8Bit ? m_end.characters8 - m_data.characters8
                                    : m_end.characters16 - m_data.characters16;
    if (matchLength < charactersCount)
        return false;
    bool matched;
    if (m_is8Bit)
        matched = WTF::equal(m_data.characters8, characters, charactersCount);
    else
        matched = WTF::equal(m_data.characters16, characters, charactersCount);
    if (matched)
        advance(charactersCount);
    return matched;
}

bool VTTScanner::scanRun(const Run& run, const String& toMatch)
{
    DCHECK_EQ(run.start(), getPosition());
    DCHECK_LE(run.start(), end());
    DCHECK_GE(run.end(), run.start());
    DCHECK_LE(run.end(), end());
    size_t matchLength = run.length();
    if (toMatch.length() > matchLength)
        return false;
    bool matched;
    if (m_is8Bit)
        matched = WTF::equal(toMatch.impl(), m_data.characters8, matchLength);
    else
        matched = WTF::equal(toMatch.impl(), m_data.characters16, matchLength);
    if (matched)
        seekTo(run.end());
    return matched;
}

void VTTScanner::skipRun(const Run& run)
{
    DCHECK_LE(run.start(), end());
    DCHECK_GE(run.end(), run.start());
    DCHECK_LE(run.end(), end());
    seekTo(run.end());
}

String VTTScanner::extractString(const Run& run)
{
    DCHECK_EQ(run.start(), getPosition());
    DCHECK_LE(run.start(), end());
    DCHECK_GE(run.end(), run.start());
    DCHECK_LE(run.end(), end());
    String s;
    if (m_is8Bit)
        s = String(m_data.characters8, run.length());
    else
        s = String(m_data.characters16, run.length());
    seekTo(run.end());
    return s;
}

String VTTScanner::restOfInputAsString()
{
    Run rest(getPosition(), end(), m_is8Bit);
    return extractString(rest);
}

unsigned VTTScanner::scanDigits(int& number)
{
    Run runOfDigits = collectWhile<isASCIIDigit>();
    if (runOfDigits.isEmpty()) {
        number = 0;
        return 0;
    }
    bool validNumber;
    size_t numDigits = runOfDigits.length();
    if (m_is8Bit)
        number = charactersToInt(m_data.characters8, numDigits, &validNumber);
    else
        number = charactersToInt(m_data.characters16, numDigits, &validNumber);

    // Since we know that scanDigits only scanned valid (ASCII) digits (and
    // hence that's what got passed to charactersToInt()), the remaining
    // failure mode for charactersToInt() is overflow, so if |validNumber| is
    // not true, then set |number| to the maximum int value.
    if (!validNumber)
        number = std::numeric_limits<int>::max();
    // Consume the digits.
    seekTo(runOfDigits.end());
    return numDigits;
}

bool VTTScanner::scanFloat(float& number)
{
    Run integerRun = collectWhile<isASCIIDigit>();
    seekTo(integerRun.end());
    Run decimalRun(getPosition(), getPosition(), m_is8Bit);
    if (scan('.')) {
        decimalRun = collectWhile<isASCIIDigit>();
        seekTo(decimalRun.end());
    }

    // At least one digit required.
    if (integerRun.isEmpty() && decimalRun.isEmpty()) {
        // Restore to starting position.
        seekTo(integerRun.start());
        return false;
    }

    size_t lengthOfFloat = Run(integerRun.start(), getPosition(), m_is8Bit).length();
    bool validNumber;
    if (m_is8Bit)
        number = charactersToFloat(integerRun.start(), lengthOfFloat, &validNumber);
    else
        number = charactersToFloat(reinterpret_cast<const UChar*>(integerRun.start()),
            lengthOfFloat, &validNumber);

    if (!validNumber)
        number = std::numeric_limits<float>::max();
    return true;
}

bool VTTScanner::scanPercentage(float& percentage)
{
    Position savedPosition = getPosition();
    if (!scanFloat(percentage))
        return false;
    if (scan('%'))
        return true;
    // Restore scanner position.
    seekTo(savedPosition);
    return false;
}

} // namespace blink
