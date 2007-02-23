//
// RegularExpression.h
//
// $Id: //poco/Main/Foundation/src/RegularExpression.cpp#12 $
//
// Library: Foundation
// Package: RegExp
// Module:  RegularExpression
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


#include "Poco/RegularExpression.h"
#include "Poco/Exception.h"
#include <sstream>
#include "pcre.h"


namespace Poco {


const int RegularExpression::OVEC_SIZE = 64;


RegularExpression::RegularExpression(const std::string& pattern, int options, bool study): _pcre(0), _extra(0)
{
	const char* error;
	int offs;
	_pcre = pcre_compile(pattern.c_str(), options, &error, &offs, 0);
	if (!_pcre)
	{
		std::ostringstream msg;
		msg << error << " (at offset " << offs << ")";
		throw RegularExpressionException(msg.str());
	}
	if (study)
		_extra = pcre_study(_pcre, 0, &error);
}


RegularExpression::~RegularExpression()
{
	if (_pcre)  pcre_free(_pcre);
	if (_extra) pcre_free(_extra);
}


int RegularExpression::match(const std::string& subject, std::string::size_type offset, Match& mtch, int options) const
{
	poco_assert (offset <= subject.length());

	int ovec[OVEC_SIZE];
	int rc = pcre_exec(_pcre, _extra, subject.c_str(), int(subject.size()), int(offset), options & 0xFFFF, ovec, OVEC_SIZE);
	if (rc == PCRE_ERROR_NOMATCH)
	{
		mtch.offset = std::string::npos;
		mtch.length = 0;
		return 0;
	}
	else if (rc == PCRE_ERROR_BADOPTION)
	{
		throw RegularExpressionException("bad option");
	}
	else if (rc == 0)
	{
		throw RegularExpressionException("too many captured substrings");
	}
	else if (rc < 0)
	{
		std::ostringstream msg;
		msg << "PCRE error " << rc;
		throw RegularExpressionException(msg.str());
	}
	mtch.offset = ovec[0] < 0 ? std::string::npos : ovec[0];
	mtch.length = ovec[1] - mtch.offset;
	return rc;
}


int RegularExpression::match(const std::string& subject, std::string::size_type offset, MatchVec& matches, int options) const
{
	poco_assert (offset <= subject.length());

	matches.clear();

	int ovec[OVEC_SIZE];
	int rc = pcre_exec(_pcre, _extra, subject.c_str(), int(subject.size()), int(offset), options & 0xFFFF, ovec, OVEC_SIZE);
	if (rc == PCRE_ERROR_NOMATCH)
	{
		return 0;
	}
	else if (rc == PCRE_ERROR_BADOPTION)
	{
		throw RegularExpressionException("bad option");
	}
	else if (rc == 0)
	{
		throw RegularExpressionException("too many captured substrings");
	}
	else if (rc < 0)
	{
		std::ostringstream msg;
		msg << "PCRE error " << rc;
		throw RegularExpressionException(msg.str());
	}
	matches.reserve(rc);
	for (int i = 0; i < rc; ++i)
	{
		Match m;
		m.offset = ovec[i*2] < 0 ? std::string::npos : ovec[i*2] ;
		m.length = ovec[i*2 + 1] - m.offset;
		matches.push_back(m);
	}
	return rc;
}


bool RegularExpression::match(const std::string& subject, std::string::size_type offset) const
{
	Match mtch;
	match(subject, offset, mtch, RE_ANCHORED | RE_NOTEMPTY);
	return mtch.offset == offset && mtch.length == subject.length() - offset;
}


bool RegularExpression::match(const std::string& subject, std::string::size_type offset, int options) const
{
	Match mtch;
	match(subject, offset, mtch, options);
	return mtch.offset == offset && mtch.length == subject.length() - offset;
}


int RegularExpression::extract(const std::string& subject, std::string& str, int options) const
{
	Match mtch;
	int rc = match(subject, 0, mtch, options);
	if (mtch.offset != std::string::npos)
		str.assign(subject, mtch.offset, mtch.length);
	else
		str.clear();
	return rc;
}


int RegularExpression::extract(const std::string& subject, std::string::size_type offset, std::string& str, int options) const
{
	Match mtch;
	int rc = match(subject, offset, mtch, options);
	if (mtch.offset != std::string::npos)
		str.assign(subject, mtch.offset, mtch.length);
	else
		str.clear();
	return rc;
}


int RegularExpression::split(const std::string& subject, std::string::size_type offset, std::vector<std::string>& strings, int options) const
{
	MatchVec matches;
	strings.clear();
	int rc = match(subject, offset, matches, options);
	strings.reserve(matches.size());
	for (MatchVec::const_iterator it = matches.begin(); it != matches.end(); ++it)
	{
		if (it->offset != std::string::npos)
			strings.push_back(subject.substr(it->offset, it->length));
		else
			strings.push_back(std::string());
	}
	return rc;
}


int RegularExpression::subst(std::string& subject, std::string::size_type offset, const std::string& replacement, int options) const
{
	if (options & RE_GLOBAL)
	{
		int rc = 0;
		std::string::size_type pos = substOne(subject, offset, replacement, options);
		while (pos != std::string::npos)
		{
			++rc;
			pos = substOne(subject, pos, replacement, options);
		}
		return rc;
	}
	else
	{
		return substOne(subject, offset, replacement, options) != std::string::npos ? 1 : 0;
	}
}


std::string::size_type RegularExpression::substOne(std::string& subject, std::string::size_type offset, const std::string& replacement, int options) const
{
	if (offset >= subject.length()) return std::string::npos;

	int ovec[OVEC_SIZE];
	int rc = pcre_exec(_pcre, _extra, subject.c_str(), int(subject.size()), int(offset), options & 0xFFFF, ovec, OVEC_SIZE);
	if (rc == PCRE_ERROR_NOMATCH)
	{
		return std::string::npos;
	}
	else if (rc == PCRE_ERROR_BADOPTION)
	{
		throw RegularExpressionException("bad option");
	}
	else if (rc == 0)
	{
		throw RegularExpressionException("too many captured substrings");
	}
	else if (rc < 0)
	{
		std::ostringstream msg;
		msg << "PCRE error " << rc;
		throw RegularExpressionException(msg.str());
	}
	std::string result;
	std::string::size_type len = subject.length();
	std::string::size_type pos = 0;
	std::string::size_type rp = std::string::npos;
	while (pos < len)
	{
		if (ovec[0] == pos)
		{
			std::string::const_iterator it  = replacement.begin();
			std::string::const_iterator end = replacement.end();
			while (it != end)
			{
				if (*it == '$' && !(options & RE_NO_VARS))
				{
					++it;
					if (it != end)
					{
						char d = *it;
						if (d >= '0' && d <= '9')
						{
							int c = d - '0';
							if (c < rc)
							{
								int o = ovec[c*2];
								int l = ovec[c*2 + 1] - o;
								result.append(subject, o, l);
							}
						}
						else
						{
							result += '$';
							result += d;
						}
						++it;
					}
					else result += '$';
				}
				else result += *it++;
			}
			pos = ovec[1];
			rp = result.length();
		}
		else result += subject[pos++];
	}
	subject = result;
	return rp;
}


bool RegularExpression::match(const std::string& subject, const std::string& pattern, int options)
{
	int ctorOptions = options & (RE_CASELESS | RE_MULTILINE | RE_DOTALL | RE_EXTENDED | RE_ANCHORED | RE_DOLLAR_ENDONLY | RE_EXTRA | RE_UNGREEDY | RE_UTF8 | RE_NO_AUTO_CAPTURE);
	int mtchOptions = options & (RE_ANCHORED | RE_NOTBOL | RE_NOTEOL | RE_NOTEMPTY | RE_NO_AUTO_CAPTURE | RE_NO_UTF8_CHECK);
	RegularExpression re(pattern, ctorOptions, false);
	return re.match(subject, 0, mtchOptions);
}


} // namespace Poco
