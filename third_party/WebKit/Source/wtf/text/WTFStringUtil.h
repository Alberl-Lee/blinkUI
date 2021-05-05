
#ifndef WTFStringUtil_h
#define WTFStringUtil_h

#include "wtf/text/WTFString.h"

namespace WTF {

String ensureUTF16String(const String& string);

Vector<UChar> ensureUTF16UChar(const String& string);

Vector<UChar> ensureStringToUChars(const String& string);

Vector<char> ensureStringToUTF8(const String& string);

String ensureStringToUTF8String(const String& string);

bool splitStringToVector(const String& strData, const char strSplit, bool needTrim, WTF::Vector<String>& out);
}

#endif // WTFStringUtil_h