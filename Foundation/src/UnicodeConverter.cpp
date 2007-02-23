//
// UnicodeConverter.cpp
//
// $Id: //poco/Main/Foundation/src/UnicodeConverter.cpp#8 $
//
// Library: Foundation
// Package: Text
// Module:  UnicodeConverter
//
// Copyright (c) 2006, Applied Informatics Software Engineering GmbH.
// and Contributors.
//
// Permission is hereby granted, free of charge, to any person or organization
// obtaining a copy of the software and accompanying documentation covered by
// this license (the "Software") to use, reproduce, display, distribute,
// execute, and transmit the Software, and to prepare derivative works of the
// Software, and to permit third-parties to whom the Software is furnished to
// do so, all subject to the following:
// 
// The copyright notices in the Software and this entire statement, including
// the above license grant, this restriction and the following disclaimer,
// must be included in all copies of the Software, in whole or in part, and
// all derivative works of the Software, unless such copies or derivative
// works are solely in the form of machine-executable object code generated by
// a source language processor.
// 
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE, TITLE AND NON-INFRINGEMENT. IN NO EVENT
// SHALL THE COPYRIGHT HOLDERS OR ANYONE DISTRIBUTING THE SOFTWARE BE LIABLE
// FOR ANY DAMAGES OR OTHER LIABILITY, WHETHER IN CONTRACT, TORT OR OTHERWISE,
// ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
// DEALINGS IN THE SOFTWARE.
//


#ifndef POCO_NO_WSTRING


#include "Poco/UnicodeConverter.h"
#include "Poco/TextConverter.h"
#include "Poco/TextIterator.h"
#include "Poco/UTF8Encoding.h"
#include "Poco/UTF16Encoding.h"
#include <string.h>
#include <wchar.h>


namespace Poco {


void UnicodeConverter::toUTF16(const std::string& utf8String, std::wstring& utf16String)
{
	utf16String.clear();
	UTF8Encoding utf8Encoding;
	TextIterator it(utf8String, utf8Encoding);
	TextIterator end(utf8String);
	while (it != end) utf16String += (wchar_t) *it++;
}


void UnicodeConverter::toUTF16(const char* utf8String, int length, std::wstring& utf16String)
{
	poco_check_ptr (utf8String);

	utf16String.clear();

	UTF8Encoding utf8Encoding;
	UTF16Encoding utf16Encoding;
	const unsigned char* it  = (const unsigned char*) utf8String;
	const unsigned char* end = (const unsigned char*) utf8String + length;
	
	while (it < end)
	{
		unsigned char c = *it;
		int n = utf8Encoding.characterMap()[c];
		int uc = '?';
		if (n == -1) 
		{
			++it;
		}
		else if (n >= 0)
		{
			uc = n;
			++it;
		}
		else
		{
			if (it - n <= end)
			{
				uc = utf8Encoding.convert(it);
				if (uc == -1) uc = '?';
			}
			it -= n;
		}
		utf16String += (wchar_t) uc; // TODO: surrogates
	}
}


void UnicodeConverter::toUTF16(const char* utf8String, std::wstring& utf16String)
{
	toUTF16(utf8String, (int) strlen(utf8String), utf16String);
}


void UnicodeConverter::toUTF8(const std::wstring& utf16String, std::string& utf8String)
{
	utf8String.clear();
	UTF8Encoding utf8Encoding;
	UTF16Encoding utf16Encoding;
	TextConverter converter(utf16Encoding, utf8Encoding);
	converter.convert(utf16String.data(), (int) utf16String.length()*sizeof(wchar_t), utf8String);
}


void UnicodeConverter::toUTF8(const wchar_t* utf16String, int length, std::string& utf8String)
{
	utf8String.clear();
	UTF8Encoding utf8Encoding;
	UTF16Encoding utf16Encoding;
	TextConverter converter(utf16Encoding, utf8Encoding);
	converter.convert(utf16String, (int) length*sizeof(wchar_t), utf8String);
}


void UnicodeConverter::toUTF8(const wchar_t* utf16String, std::string& utf8String)
{
	toUTF8(utf16String, (int) wcslen(utf16String), utf8String);
}


} // namespace Poco


#endif // POCO_NO_WSTRING
