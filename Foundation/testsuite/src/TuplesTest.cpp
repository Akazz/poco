//
// TuplesTest.cpp
//
// $Id: //poco/Main/Foundation/testsuite/src/TuplesTest.cpp#4 $
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


#include "TuplesTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/Tuple.h"
#include "Poco/Void.h"


using Poco::TypeList;
using Poco::NullTypeList;
using Poco::TypeListType;
using Poco::TypeGetter;
using Poco::TypeLocator;
using Poco::TypeAppender;
using Poco::TypeOneEraser;
using Poco::TypeAllEraser;
using Poco::TypeDuplicateEraser;
using Poco::TypeOneReplacer;
using Poco::TypeAllReplacer;
using Poco::Tuple;
using Poco::Void;
using Poco::Int8;
using Poco::UInt8;
using Poco::Int16;
using Poco::UInt16;
using Poco::Int32;
using Poco::UInt32;
using Poco::Int8;
using Poco::UInt8;
using Poco::Int16;
using Poco::UInt16;
using Poco::Int32;
using Poco::UInt32;


TuplesTest::TuplesTest(const std::string& name): CppUnit::TestCase(name)
{
}


TuplesTest::~TuplesTest()
{
}


void TuplesTest::testTuple1()
{
	Tuple<int> t;
	assert (t.length == 1);
	t.set<0>(-1);
	assert (t.get<0>() == -1);
	
	Tuple<int> t2(-1);
	assert (t2.get<0>() == -1);

	Tuple<int> tCpy (t2);
	assert (t2.get<0>() == tCpy.get<0>());
	assert (t2 == tCpy);

	Tuple<int> tCpy2 = t2;
	assert (t2.get<0>() == tCpy2.get<0>());
	assert (t2 == tCpy2);
	tCpy2.set<0>(888);
	assert (t2 != tCpy2);
	assert (t < tCpy2);

	Tuple<int, std::string> t3(0);
	assert (t3.get<1>().empty());

	Tuple<int, std::string, std::vector<std::string> > t4(0);
	assert (t4.get<1>().empty());
	assert (t4.get<2>().empty());
}


void TuplesTest::testTuple2()
{
	Tuple<int, Void> dummy1;
	assert (dummy1.length == 2);
	dummy1.set<0>(-1);
	assert (dummy1.get<0>() == -1);
	//test partial init
	Tuple<int, Void> dummy11(0);

	Tuple<Void, int> dummy2;
	dummy2.set<1>(-1);
	assert (dummy2.get<1>() == -1);

	Tuple<Void, int> dummy3;
	dummy3.set<1>(-1);
	assert (dummy3.get<1>() == -1);

	Tuple<std::string, int> aTuple;
	aTuple.set<0>("str");
	aTuple.set<1>(1);
	assert (aTuple.get<0>() == "str");
	assert (aTuple.get<1>() == 1);

	Tuple<std::string, int> aTuple2(aTuple);
	assert (aTuple == aTuple2);
	aTuple2.set<1>(99);
	assert (aTuple != aTuple2);
	aTuple2.set<1>(100000);
	assert (aTuple < aTuple2);
}


void TuplesTest::testTuple3()
{
	Tuple<int, Void, Void> dummy1;
	assert (dummy1.length == 3);
	dummy1.set<0>(-1);
	assert (dummy1.get<0>() == -1);
	//test partial init
	Tuple<int, Void, Void> dummy11(0);

	Tuple<Void, int, Void> dummy2;
	dummy2.set<1>(-1);
	assert (dummy2.get<1>() == -1);

	Tuple<Void, Void, int> dummy3;
	dummy3.set<2>(-1);
	assert (dummy3.get<2>() == -1);

	Tuple<std::string, int, bool> aTuple;
	aTuple.set<0>("str");
	aTuple.set<1>(1);
	aTuple.set<2>(true);
	assert (aTuple.get<0>() == "str");
	assert (aTuple.get<1>() == 1);
	assert (aTuple.get<2>());

	Tuple<std::string, int, bool> aTuple2(aTuple);
	assert (aTuple == aTuple2);
	aTuple2.set<2>(false);
	assert (aTuple != aTuple2);
	aTuple2.set<1>(100000);
	assert (aTuple < aTuple2);
}


void TuplesTest::testTuple4()
{
	Tuple<int, Void, Void, Void> dummy1;
	assert (dummy1.length == 4);
	dummy1.set<0>(-1);
	assert (dummy1.get<0>() == -1);
	//test partial init
	Tuple<int, Void, Void, Void> dummy11(0);

	Tuple<Void, int, Void, Void> dummy2;
	dummy2.set<1>(-1);
	assert (dummy2.get<1>() == -1);

	Tuple<Void, Void, Void, int> dummy3;
	dummy3.set<3>(-1);
	assert (dummy3.get<3>() == -1);

	Tuple<std::string, int, bool, float> aTuple;
	aTuple.set<0>("str");
	aTuple.set<1>(1);
	aTuple.set<2>(true);
	aTuple.set<3>(3.14f);
	assert (aTuple.get<0>() == "str");
	assert (aTuple.get<1>() == 1);
	assert (aTuple.get<2>());
	assert (aTuple.get<3>() >= 3.13f && aTuple.get<3>() <= 3.15f);

	Tuple<std::string, int, bool, float> aTuple2(aTuple);
	assert (aTuple == aTuple2);
	aTuple2.set<2>(false);
	assert (aTuple != aTuple2);
	aTuple2.set<1>(100000);
	assert (aTuple < aTuple2);
}


void TuplesTest::testTuple5()
{
	Tuple<int, Void, Void, Void, Void> dummy1;
	assert (dummy1.length == 5);
	dummy1.set<0>(-1);
	assert (dummy1.get<0>() == -1);
	//test partial init
	Tuple<int, Void, Void, Void, Void> dummy11(0);

	Tuple<Void, int, Void, Void, Void> dummy2;
	dummy2.set<1>(-1);
	assert (dummy2.get<1>() == -1);

	Tuple<Void, Void, Void, Void, int> dummy3;
	dummy3.set<4>(-1);
	assert (dummy3.get<4>() == -1);

	Tuple<std::string, int, bool, float, char> aTuple;
	aTuple.set<0>("str");
	aTuple.set<1>(1);
	aTuple.set<2>(true);
	aTuple.set<3>(3.14f);
	aTuple.set<4>(' ');
	assert (aTuple.get<0>() == "str");
	assert (aTuple.get<1>() == 1);
	assert (aTuple.get<2>());
	assert (aTuple.get<3>() >= 3.13f && aTuple.get<3>() <= 3.15f);
	assert (aTuple.get<4>() == ' ');

	Tuple<std::string, int, bool, float, char> aTuple2(aTuple);
	assert (aTuple == aTuple2);
	aTuple2.set<2>(false);
	assert (aTuple != aTuple2);
	aTuple2.set<1>(100000);
	assert (aTuple < aTuple2);
}


void TuplesTest::testTuple6()
{
	Tuple<std::string, int, bool, float, char, long> aTuple;
	assert (aTuple.length == 6);
	Tuple<std::string, int, bool, float, char, long> 
		aTuple2("1", 1, true, 3.14f, 'c', 999);
	assert (aTuple != aTuple2);
	aTuple = aTuple2;
	assert (aTuple == aTuple2);
	aTuple2.get<1>()++;
	assert (aTuple < aTuple2);
}


void TuplesTest::testTuple7()
{
	Tuple<std::string, int, bool, float, char, long, double> aTuple;
	assert (aTuple.length == 7);
	Tuple<std::string, int, bool, float, char, long, double> 
		aTuple2("1", 1, true, 3.14f, 'c', 999, 33.14);
	assert (aTuple != aTuple2);
	aTuple = aTuple2;
	assert (aTuple == aTuple2);
	aTuple2.get<1>()++;
	assert (aTuple < aTuple2);
}


void TuplesTest::testTuple8()
{
	Tuple<std::string, int, bool, float, char, long, double, short> aTuple;
	assert (aTuple.length == 8);
	Tuple<std::string, int, bool, float, char, long, double, short> 
		aTuple2("1", 1, true, 3.14f, 'c', 999, 33.14, 32700);
	assert (aTuple != aTuple2);
	aTuple = aTuple2;
	assert (aTuple == aTuple2);
	aTuple2.get<1>()++;
	assert (aTuple < aTuple2);
}

void TuplesTest::testTuple9()
{
	Tuple<std::string, int, bool, float, char, long, double, short, std::string> aTuple;
	assert (aTuple.length == 9);
	Tuple<std::string, int, bool, float, char, long, double, short, std::string> 
		aTuple2("1", 1, true, 3.14f, 'c', 999, 33.14, 32700, "2");
	assert (aTuple != aTuple2);
	aTuple = aTuple2;
	assert (aTuple == aTuple2);
	aTuple2.get<1>()++;
	assert (aTuple < aTuple2);
}


void TuplesTest::testTuple10()
{
	typedef Tuple<std::string, int, bool, float, char, long, double, short, std::string, int> TupleType;

	TupleType aTuple;
	assert (aTuple.length == 10);
	TupleType aTuple2("1", 1, true, 3.14f, 'c', 999, 33.14, 32700, "2", 2);
	assert (aTuple != aTuple2);
	aTuple = aTuple2;
	assert (aTuple == aTuple2);
	aTuple2.get<1>()++;
	assert (aTuple < aTuple2);
}


void TuplesTest::testTuple11()
{
	typedef Tuple<std::string, int, bool, float, char, long, double, short, std::string, int, 
		std::string> TupleType;

	TupleType aTuple;
	assert (aTuple.length == 11);
	TupleType aTuple2("1", 1, true, 3.14f, 'c', 999, 33.14, 32700, "2", 2, "1");
	assert (aTuple != aTuple2);
	aTuple = aTuple2;
	assert (aTuple == aTuple2);
	aTuple2.get<1>()++;
	assert (aTuple < aTuple2);
}


void TuplesTest::testTuple12()
{
	typedef Tuple<std::string, int, bool, float, char, long, double, short, std::string, int, 
		std::string, int> TupleType;

	TupleType aTuple;
	assert (aTuple.length == 12);
	TupleType aTuple2("1", 1, true, 3.14f, 'c', 999, 33.14, 32700, "2", 2, "1", 1);
	assert (aTuple != aTuple2);
	aTuple = aTuple2;
	assert (aTuple == aTuple2);
	aTuple2.get<1>()++;
	assert (aTuple < aTuple2);
}


void TuplesTest::testTuple13()
{
	typedef Tuple<std::string, int, bool, float, char, long, double, short, std::string, int, 
		std::string, int, bool> TupleType;

	TupleType aTuple;
	assert (aTuple.length == 13);
	TupleType aTuple2("1", 1, true, 3.14f, 'c', 999, 33.14, 32700, "2", 2, "1", 1, true);
	assert (aTuple != aTuple2);
	aTuple = aTuple2;
	assert (aTuple == aTuple2);
	aTuple2.get<1>()++;
	assert (aTuple < aTuple2);
}


void TuplesTest::testTuple14()
{
	typedef Tuple<std::string, int, bool, float, char, long, double, short, std::string, int, 
		std::string, int, bool, float> TupleType;

	TupleType aTuple;
	assert (aTuple.length == 14);
	TupleType aTuple2("1", 1, true, 3.14f, 'c', 999, 33.14, 32700, "2", 2, "1", 1, true, 3.14f);
	assert (aTuple != aTuple2);
	aTuple = aTuple2;
	assert (aTuple == aTuple2);
	aTuple2.get<1>()++;
	assert (aTuple < aTuple2);
}


void TuplesTest::testTuple15()
{
	typedef Tuple<std::string, int, bool, float, char, long, double, short, std::string, int, 
		std::string, int, bool, float, char> TupleType;

	TupleType aTuple;
	assert (aTuple.length == 15);
	TupleType aTuple2("1", 1, true, 3.14f, 'c', 999, 33.14, 32700, "2", 2, "1", 1, true, 3.14f, 'c');
	assert (aTuple != aTuple2);
	aTuple = aTuple2;
	assert (aTuple == aTuple2);
	aTuple2.get<1>()++;
	assert (aTuple < aTuple2);
}


void TuplesTest::testTuple16()
{
	typedef Tuple<std::string, int, bool, float, char, long, double, short, std::string, int, 
		std::string, int, bool, float, char, long> TupleType;

	TupleType aTuple;
	assert (aTuple.length == 16);
	TupleType aTuple2("1", 1, true, 3.14f, 'c', 999, 33.14, 32700, "2", 2, "1", 1, true, 3.14f, 'c', 999);
	assert (aTuple != aTuple2);
	aTuple = aTuple2;
	assert (aTuple == aTuple2);
	aTuple2.get<1>()++;
	assert (aTuple < aTuple2);
}


void TuplesTest::testTuple17()
{
	typedef Tuple<std::string, int, bool, float, char, long, double, short, std::string, int, 
		std::string, int, bool, float, char, long, double> TupleType;

	TupleType aTuple;
	assert (aTuple.length == 17);
	TupleType aTuple2("1", 1, true, 3.14f, 'c', 999, 33.14, 32700, "2", 2, "1", 1, true, 3.14f, 'c', 999, 33.14);
	assert (aTuple != aTuple2);
	aTuple = aTuple2;
	assert (aTuple == aTuple2);
	aTuple2.get<1>()++;
	assert (aTuple < aTuple2);
}


void TuplesTest::testTuple18()
{
	typedef Tuple<std::string, int, bool, float, char, long, double, short, std::string, int, 
		std::string, int, bool, float, char, long, double, short> TupleType;

	TupleType aTuple;
	assert (aTuple.length == 18);
	TupleType aTuple2("1", 1, true, 3.14f, 'c', 999, 33.14, 32700, "2", 2, "1", 1, true, 3.14f, 'c', 999, 33.14, 32700);
	assert (aTuple != aTuple2);
	aTuple = aTuple2;
	assert (aTuple == aTuple2);
	aTuple2.get<1>()++;
	assert (aTuple < aTuple2);
}


void TuplesTest::testTuple19()
{
	typedef Tuple<std::string, int, bool, float, char, long, double, short, std::string, int, 
		std::string, int, bool, float, char, long, double, short, std::string> TupleType;

	TupleType aTuple;
	assert (aTuple.length == 19);
	TupleType aTuple2("1", 1, true, 3.14f, 'c', 999, 33.14, 32700, "2", 2, "1", 1, true, 3.14f, 'c', 999, 33.14, 32700, "2");
	assert (aTuple != aTuple2);
	aTuple = aTuple2;
	assert (aTuple == aTuple2);
	aTuple2.get<1>()++;
	assert (aTuple < aTuple2);
}


void TuplesTest::testTuple20()
{
	typedef Tuple<std::string, int, bool, float, char, long, double, short, std::string, int, 
		std::string, int, bool, float, char, long, double, short, std::string, int> TupleType;

	TupleType aTuple;
	assert (aTuple.length == 20);
	
	TupleType aTuple2("1", 1, true, 3.14f, 'c', 999, 33.14, 32700, "2", 2, "1", 1, true, 3.14f, 'c', 999, 33.14, 32700, "2", 2);
	assert (aTuple != aTuple2);
	aTuple = aTuple2;
	assert (aTuple == aTuple2);
	aTuple2.get<1>()++;
	assert (aTuple < aTuple2);
}


void TuplesTest::testMemOverhead()
{
	Tuple<short> small(0);
	int sz = sizeof(small);
	assert (sz == 4 || sz == 8); //depending on architecture and alignment
	Tuple<long> notSoSmall(0);
	sz = sizeof(notSoSmall);
	assert (sz == 8 || sz == 16); //depending on architecture and alignment
}


void TuplesTest::setUp()
{
}


void TuplesTest::tearDown()
{
}


CppUnit::Test* TuplesTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("TuplesTest");

	CppUnit_addTest(pSuite, TuplesTest, testTuple1);
	CppUnit_addTest(pSuite, TuplesTest, testTuple2);
	CppUnit_addTest(pSuite, TuplesTest, testTuple3);
	CppUnit_addTest(pSuite, TuplesTest, testTuple4);
	CppUnit_addTest(pSuite, TuplesTest, testTuple5);
	CppUnit_addTest(pSuite, TuplesTest, testTuple6);
	CppUnit_addTest(pSuite, TuplesTest, testTuple7);
	CppUnit_addTest(pSuite, TuplesTest, testTuple8);
	CppUnit_addTest(pSuite, TuplesTest, testTuple9);
	CppUnit_addTest(pSuite, TuplesTest, testTuple10);
	CppUnit_addTest(pSuite, TuplesTest, testTuple11);
	CppUnit_addTest(pSuite, TuplesTest, testTuple12);
	CppUnit_addTest(pSuite, TuplesTest, testTuple13);
	CppUnit_addTest(pSuite, TuplesTest, testTuple14);
	CppUnit_addTest(pSuite, TuplesTest, testTuple15);
	CppUnit_addTest(pSuite, TuplesTest, testTuple16);
	CppUnit_addTest(pSuite, TuplesTest, testTuple17);
	CppUnit_addTest(pSuite, TuplesTest, testTuple18);
	CppUnit_addTest(pSuite, TuplesTest, testTuple19);
	CppUnit_addTest(pSuite, TuplesTest, testTuple20);
	CppUnit_addTest(pSuite, TuplesTest, testMemOverhead);

	return pSuite;
}
