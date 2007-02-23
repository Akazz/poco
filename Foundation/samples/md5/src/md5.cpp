//
// md5.cpp
//
// $Id: //poco/Main/Foundation/samples/md5/src/md5.cpp#9 $
//
// This sample demonstrates the DigestEngine, DigestOutputStream and
// MD5Engine classes.
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


#include "Poco/MD5Engine.h"
#include "Poco/DigestStream.h"
#include "Poco/StreamCopier.h"
#include <fstream>
#include <iostream>


using Poco::DigestEngine;
using Poco::MD5Engine;
using Poco::DigestOutputStream;
using Poco::StreamCopier;


int main(int argc, char** argv)
{
	if (argc != 2)
	{
		std::cout << "usage: " << argv[0] << ": <input_file>" << std::endl
		          << "       create the MD5 digest for <input_file>" << std::endl;
		return 1;
	}
	
	std::ifstream istr(argv[1], std::ios::binary);
	if (!istr)
	{
		std::cerr << "cannot open input file: " << argv[1] << std::endl;
		return 2;
	}
	
	MD5Engine md5;
	DigestOutputStream dos(md5);
	
	StreamCopier::copyStream(istr, dos);
	dos.close();

	std::cout << DigestEngine::digestToHex(md5.digest()) << std::endl;
	
	return 0;
}
