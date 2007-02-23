//
// NumberFormatterTest.cpp
//
// $Id: //poco/Main/Foundation/testsuite/src/NumberFormatterTest.cpp#9 $
//
// Copyright (c) 2004-2006, Applied Informatics Software Engineering GmbH.
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


#include "NumberFormatterTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/NumberFormatter.h"


using Poco::NumberFormatter;
using Poco::Int64;
using Poco::UInt64;


NumberFormatterTest::NumberFormatterTest(const std::string& name): CppUnit::TestCase(name)
{
}


NumberFormatterTest::~NumberFormatterTest()
{
}


void NumberFormatterTest::testFormat()
{
	assert (NumberFormatter::format(123) == "123");
	assert (NumberFormatter::format(-123) == "-123");
	assert (NumberFormatter::format(-123, 5) == " -123");

	assert (NumberFormatter::format((unsigned) 123) == "123");
	assert (NumberFormatter::format((unsigned) 123, 5) == "  123");
	assert (NumberFormatter::format0((unsigned) 123, 5) == "00123");
	
	assert (NumberFormatter::format((long) 123) == "123");
	assert (NumberFormatter::format((long) -123) == "-123");
	assert (NumberFormatter::format((long) -123, 5) == " -123");

	assert (NumberFormatter::format((unsigned long) 123) == "123");
	assert (NumberFormatter::format((unsigned long) 123, 5) == "  123");	

#if defined(POCO_HAVE_INT64)
	assert (NumberFormatter::format((Int64) 123) == "123");
	assert (NumberFormatter::format((Int64) -123) == "-123");
	assert (NumberFormatter::format((Int64) -123, 5) == " -123");

	assert (NumberFormatter::format((UInt64) 123) == "123");
	assert (NumberFormatter::format((UInt64) 123, 5) == "  123");	
#endif

	if (sizeof(void*) == 4)
	{
		assert (NumberFormatter::format((void*) 0x12345678) == "12345678");
	}
	else
	{
		assert (NumberFormatter::format((void*) 0x12345678) == "0000000012345678");
	}
	
	assert (NumberFormatter::format(12.25) == "12.25");
	assert (NumberFormatter::format(12.25, 4) == "12.2500");
	assert (NumberFormatter::format(12.25, 8, 4) == " 12.2500");
}


void NumberFormatterTest::testFormat0()
{
	assert (NumberFormatter::format0(123, 5) == "00123");
	assert (NumberFormatter::format0(-123, 5) == "-0123");
	assert (NumberFormatter::format0((long) 123, 5) == "00123");
	assert (NumberFormatter::format0((long) -123, 5) == "-0123");
	assert (NumberFormatter::format0((unsigned long) 123, 5) == "00123");

#if defined(POCO_HAVE_INT64)
	assert (NumberFormatter::format0((Int64) 123, 5) == "00123");
	assert (NumberFormatter::format0((Int64) -123, 5) == "-0123");
	assert (NumberFormatter::format0((UInt64) 123, 5) == "00123");
#endif
}


void NumberFormatterTest::testFormatHex()
{
	assert (NumberFormatter::formatHex(0x12) == "12");
	assert (NumberFormatter::formatHex(0xab) == "AB");
	assert (NumberFormatter::formatHex(0x12, 4) == "0012");
	assert (NumberFormatter::formatHex(0xab, 4) == "00AB");

	assert (NumberFormatter::formatHex((unsigned) 0x12) == "12");
	assert (NumberFormatter::formatHex((unsigned) 0xab) == "AB");
	assert (NumberFormatter::formatHex((unsigned) 0x12, 4) == "0012");
	assert (NumberFormatter::formatHex((unsigned) 0xab, 4) == "00AB");

	assert (NumberFormatter::formatHex((long) 0x12) == "12");
	assert (NumberFormatter::formatHex((long) 0xab) == "AB");
	assert (NumberFormatter::formatHex((long) 0x12, 4) == "0012");
	assert (NumberFormatter::formatHex((long) 0xab, 4) == "00AB");

	assert (NumberFormatter::formatHex((unsigned long) 0x12) == "12");
	assert (NumberFormatter::formatHex((unsigned long) 0xab) == "AB");
	assert (NumberFormatter::formatHex((unsigned long) 0x12, 4) == "0012");
	assert (NumberFormatter::formatHex((unsigned long) 0xab, 4) == "00AB");

#if defined(POCO_HAVE_INT64)
	assert (NumberFormatter::formatHex((Int64) 0x12) == "12");
	assert (NumberFormatter::formatHex((Int64) 0xab) == "AB");
	assert (NumberFormatter::formatHex((Int64) 0x12, 4) == "0012");
	assert (NumberFormatter::formatHex((Int64) 0xab, 4) == "00AB");

	assert (NumberFormatter::formatHex((UInt64) 0x12) == "12");
	assert (NumberFormatter::formatHex((UInt64) 0xab) == "AB");
	assert (NumberFormatter::formatHex((UInt64) 0x12, 4) == "0012");
	assert (NumberFormatter::formatHex((UInt64) 0xab, 4) == "00AB");
#endif
}


void NumberFormatterTest::setUp()
{
}


void NumberFormatterTest::tearDown()
{
}


CppUnit::Test* NumberFormatterTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("NumberFormatterTest");

	CppUnit_addTest(pSuite, NumberFormatterTest, testFormat);
	CppUnit_addTest(pSuite, NumberFormatterTest, testFormat0);
	CppUnit_addTest(pSuite, NumberFormatterTest, testFormatHex);

	return pSuite;
}
