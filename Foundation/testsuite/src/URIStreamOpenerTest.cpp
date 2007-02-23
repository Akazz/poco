//
// URIStreamOpenerTest.cpp
//
// $Id: //poco/Main/Foundation/testsuite/src/URIStreamOpenerTest.cpp#10 $
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


#include "URIStreamOpenerTest.h"
#include "CppUnit/TestCaller.h"
#include "CppUnit/TestSuite.h"
#include "Poco/URIStreamOpener.h"
#include "Poco/URIStreamFactory.h"
#include "Poco/URI.h"
#include "Poco/TemporaryFile.h"
#include "Poco/Path.h"
#include <fstream>
#include <sstream>


using Poco::URIStreamOpener;
using Poco::URIStreamFactory;
using Poco::URI;
using Poco::TemporaryFile;
using Poco::Path;


namespace
{
	class StringStreamFactory: public URIStreamFactory
	{
	public:
		StringStreamFactory()
		{
		}
		
		std::istream* open(const URI& uri)
		{
			return new std::istringstream(uri.toString());
		}
	};
}


URIStreamOpenerTest::URIStreamOpenerTest(const std::string& name): CppUnit::TestCase(name)
{
}


URIStreamOpenerTest::~URIStreamOpenerTest()
{
}


void URIStreamOpenerTest::testStreamOpenerFile()
{
	TemporaryFile tempFile;
	std::string path = tempFile.path();
	std::ofstream ostr(path.c_str());
	assert (ostr.good());
	ostr << "Hello, world!" << std::endl;
	ostr.close();
	
	URI uri;
	uri.setScheme("file");
	uri.setPath(Path(path).toString(Path::PATH_UNIX));
	std::string uriString = uri.toString();
	
	URIStreamOpener opener;
	std::istream* istr = opener.open(uri);
	assert (istr != 0);
	assert (istr->good());
	delete istr;
}


void URIStreamOpenerTest::testStreamOpenerRelative()
{
	TemporaryFile tempFile;
	std::string path = tempFile.path();
	std::ofstream ostr(path.c_str());
	assert (ostr.good());
	ostr << "Hello, world!" << std::endl;
	ostr.close();
	
	URI uri(Path(path).toString(Path::PATH_UNIX));
	std::string uriString = uri.toString();
	
	URIStreamOpener opener;
	std::istream* istr = opener.open(uri);
	assert (istr != 0);
	assert (istr->good());
	delete istr;
}


void URIStreamOpenerTest::testStreamOpenerURI()
{
	TemporaryFile tempFile;
	std::string path = tempFile.path();
	std::ofstream ostr(path.c_str());
	assert (ostr.good());
	ostr << "Hello, world!" << std::endl;
	ostr.close();
	
	URI uri;
	uri.setScheme("file");
	uri.setPath(Path(path).toString(Path::PATH_UNIX));
	std::string uriString = uri.toString();
	
	URIStreamOpener opener;
	std::istream* istr = opener.open(uriString);
	assert (istr != 0);
	assert (istr->good());
	delete istr;
}


void URIStreamOpenerTest::testStreamOpenerURIResolve()
{
	TemporaryFile tempFile;
	std::string path = tempFile.path();
	std::ofstream ostr(path.c_str());
	assert (ostr.good());
	ostr << "Hello, world!" << std::endl;
	ostr.close();
	
	Path p(path);
	p.makeAbsolute();
	Path parent(p.parent());
	
	URI uri;
	uri.setScheme("file");
	uri.setPath(parent.toString(Path::PATH_UNIX));
	std::string uriString = uri.toString();
	
	URIStreamOpener opener;
	std::istream* istr = opener.open(uriString, p.getFileName());
	assert (istr != 0);
	assert (istr->good());
	delete istr;
}


void URIStreamOpenerTest::testStreamOpenerPath()
{
	TemporaryFile tempFile;
	std::string path = tempFile.path();
	std::ofstream ostr(path.c_str());
	assert (ostr.good());
	ostr << "Hello, world!" << std::endl;
	ostr.close();
		
	URIStreamOpener opener;
	std::istream* istr = opener.open(path);
	assert (istr != 0);
	assert (istr->good());
	delete istr;
}


void URIStreamOpenerTest::testStreamOpenerPathResolve()
{
	TemporaryFile tempFile;
	std::string path = tempFile.path();
	std::ofstream ostr(path.c_str());
	assert (ostr.good());
	ostr << "Hello, world!" << std::endl;
	ostr.close();
	
	Path p(path);
	Path parent(p.parent());
	std::string base = parent.toString();
		
	URIStreamOpener opener;
	std::istream* istr = opener.open(base, p.getFileName());
	assert (istr != 0);
	assert (istr->good());
	delete istr;
}


void URIStreamOpenerTest::testRegisterUnregister()
{
	URIStreamOpener opener;
	assert (!opener.supportsScheme("string"));
	opener.registerStreamFactory("string", new StringStreamFactory);
	assert (opener.supportsScheme("string"));
	URI uri("string:foobar");
	std::istream* istr = opener.open(uri);
	assert (istr != 0);
	assert (istr->good());
	delete istr;
	opener.unregisterStreamFactory("string");
	assert (!opener.supportsScheme("string"));
}


void URIStreamOpenerTest::setUp()
{
}


void URIStreamOpenerTest::tearDown()
{
}


CppUnit::Test* URIStreamOpenerTest::suite()
{
	CppUnit::TestSuite* pSuite = new CppUnit::TestSuite("URIStreamOpenerTest");

	CppUnit_addTest(pSuite, URIStreamOpenerTest, testStreamOpenerFile);
	CppUnit_addTest(pSuite, URIStreamOpenerTest, testStreamOpenerRelative);
	CppUnit_addTest(pSuite, URIStreamOpenerTest, testStreamOpenerURI);
	CppUnit_addTest(pSuite, URIStreamOpenerTest, testStreamOpenerURIResolve);
	CppUnit_addTest(pSuite, URIStreamOpenerTest, testStreamOpenerPath);
	CppUnit_addTest(pSuite, URIStreamOpenerTest, testStreamOpenerPathResolve);
	CppUnit_addTest(pSuite, URIStreamOpenerTest, testRegisterUnregister);

	return pSuite;
}
