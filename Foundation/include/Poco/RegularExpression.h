//
// RegularExpression.h
//
// $Id: //poco/Main/Foundation/include/Poco/RegularExpression.h#4 $
//
// Library: Foundation
// Package: RegExp
// Module:  RegularExpression
//
// Definitions of class RegularExpression.
//
// A wrapper class for Philip Hazel's PCRE - Perl Compatible Regular Expressions
// library (http://www.pcre.org).
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


#ifndef Foundation_RegularExpression_INCLUDED
#define Foundation_RegularExpression_INCLUDED


#include "Poco/Foundation.h"
#include <vector>


//
// Copy these definitions from pcre.h
// to avoid pulling in the entire header file
//
extern "C"
{
	struct real_pcre;
	typedef struct real_pcre pcre;
	struct pcre_extra;
}


namespace Poco {


class Foundation_API RegularExpression
	/// A class for working with regular expressions.
	/// Implemented using PCRE, the Perl Compatible
	/// Regular Expressions library by Philip Hazel
	/// (see http://www.pcre.org).
	///
	/// An overload of operator ^ is provided for
	/// simple matching.
{
public:
	enum Options // These must match the corresponsing options in pcre.h!
		/// Some of the following options can only be passed to the constructor;
		/// some can be passed only to matching functions, and some can be used
		/// everywhere.
		/// 
		/// * Options marked [ctor] can be passed to the constructor.
		/// * Options marked [match] can be passed to match, extract, split and subst.
		/// * Options marked [subst] can be passed to subst.
		///
		/// See the PCRE documentation for more information.
	{
		RE_CASELESS        = 0x00001, /// case insensitive matching (/i) [ctor]
		RE_MULTILINE       = 0x00002, /// enable multi-line mode; affects ^ and $ (/m) [ctor]
		RE_DOTALL          = 0x00004, /// dot matches all characters, including newline (/s) [ctor]
		RE_EXTENDED        = 0x00004, /// totally ignore whitespace (/x) [ctor]
		RE_ANCHORED        = 0x00010, /// treat pattern as if it starts with a ^ [ctor, match]
		RE_DOLLAR_ENDONLY  = 0x00020, /// dollar matches end-of-string only, not last newline in string [ctor]
		RE_EXTRA           = 0x00040, /// enable optional PCRE functionality [ctor]
		RE_NOTBOL          = 0x00080, /// circumflex does not match beginning of string [match]
		RE_NOTEOL          = 0x00100, /// $ does not match end of string [match]
		RE_UNGREEDY        = 0x00200, /// make quantifiers ungreedy [ctor]
		RE_NOTEMPTY        = 0x00400, /// empty string never matches [match]
		RE_UTF8            = 0x00800, /// assume pattern and subject is UTF-8 encoded [ctor]
		RE_NO_AUTO_CAPTURE = 0x01000, /// disable numbered capturing parentheses [ctor, match]
		RE_NO_UTF8_CHECK   = 0x02000, /// do not check validity of UTF-8 code sequences [match]
		RE_GLOBAL          = 0x10000, /// replace all occurences (/g) [subst]
		RE_NO_VARS         = 0x20000  /// treat dollar in replacement string as ordinary character [subst]
	};
	
	struct Match
	{
		std::string::size_type offset; /// zero based offset (std::string::npos if subexpr does not match)
		std::string::size_type length; /// length of substring
	};
	typedef std::vector<Match> MatchVec;
	
	RegularExpression(const std::string& pattern, int options = 0, bool study = true);
		/// Creates a regular expression and parses the given pattern.
		/// If study is true, the pattern is analyzed and optimized. This
		/// is mainly useful if the pattern is used more than once.
		/// For a description of the options, please see the PCRE documentation.
		/// Throws a RegularExpressionException if the patter cannot be compiled.
		
	~RegularExpression();
		/// Destroys the regular expression.

	int match(const std::string& subject, Match& mtch, int options = 0) const;
		/// Matches the given subject string against the pattern. Returns the position
		/// of the first captured substring in mtch.
		/// If no part of the subject matches the pattern, mtch.offset is std::string::npos and
		/// mtch.length is 0.
		/// Throws a RegularExpressionException in case of an error.
		/// Returns the number of matches.

	int match(const std::string& subject, std::string::size_type offset, Match& mtch, int options = 0) const;
		/// Matches the given subject string, starting at offset, against the pattern. 
		/// Returns the position of the captured substring in mtch.
		/// If no part of the subject matches the pattern, mtch.offset is std::string::npos and
		/// mtch.length is 0.
		/// Throws a RegularExpressionException in case of an error.
		/// Returns the number of matches.

	int match(const std::string& subject, std::string::size_type offset, MatchVec& matches, int options = 0) const;
		/// Matches the given subject string against the pattern. 
		/// The first entry in matches contains the position of the captured substring.
		/// The following entries identify matching subpatterns. See the PCRE documentation
		/// for a more detailed explanation.
		/// If no part of the subject matches the pattern, matches is empty.
		/// Throws a RegularExpressionException in case of an error.
		/// Returns the number of matches.

	bool match(const std::string& subject, std::string::size_type offset = 0) const;
		/// Returns true if and only if the subject matches the regular expression.
		///
		/// Internally, this method sets the RE_ANCHORED and RE_NOTEMPTY options for
		/// matching, which means that the empty string will never match and
		/// the pattern is treated as if it starts with a ^.

	bool match(const std::string& subject, std::string::size_type offset, int options) const;
		/// Returns true if and only if the subject matches the regular expression.

	int extract(const std::string& subject, std::string& str, int options = 0) const;
		/// Matches the given subject string against the pattern. 
		/// Returns the captured string.
		/// Throws a RegularExpressionException in case of an error.
		/// Returns the number of matches.

	int extract(const std::string& subject, std::string::size_type offset, std::string& str, int options = 0) const;
		/// Matches the given subject string, starting at offset, against the pattern. 
		/// Returns the captured string.
		/// Throws a RegularExpressionException in case of an error.
		/// Returns the number of matches.

	int split(const std::string& subject, std::vector<std::string>& strings, int options = 0) const;
		/// Matches the given subject string against the pattern. 
		/// The first entry in captured is the captured substring.
		/// The following entries contain substrings matching subpatterns. See the PCRE documentation
		/// for a more detailed explanation.
		/// If no part of the subject matches the pattern, captured is empty.
		/// Throws a RegularExpressionException in case of an error.
		/// Returns the number of matches.

	int split(const std::string& subject, std::string::size_type offset, std::vector<std::string>& strings, int options = 0) const;
		/// Matches the given subject string against the pattern. 
		/// The first entry in captured is the captured substring.
		/// The following entries contain substrings matching subpatterns. See the PCRE documentation
		/// for a more detailed explanation.
		/// If no part of the subject matches the pattern, captured is empty.
		/// Throws a RegularExpressionException in case of an error.
		/// Returns the number of matches.
	
	int subst(std::string& subject, const std::string& replacement, int options = 0) const;
		/// Substitute in subject all matches of the pattern with replacement.
		/// If RE_GLOBAL is specified as option, all matches are replaced. Otherwise,
		/// only the first match is replaced.
		/// Occurences of $<n> (for example, $1, $2, ...) in replacement are replaced 
		/// with the corresponding captured string. $0 is the original subject string.
		/// Returns the number of replaced occurences.

	int subst(std::string& subject, std::string::size_type offset, const std::string& replacement, int options = 0) const;
		/// Substitute in subject all matches of the pattern with replacement,
		/// starting at offset.
		/// If RE_GLOBAL is specified as option, all matches are replaced. Otherwise,
		/// only the first match is replaced.
		/// Unless RE_NO_VARS is specified, occurences of $<n> (for example, $0, $1, $2, ... $9) 
		/// in replacement are replaced with the corresponding captured string. 
		/// $0 is the captured substring. $1 ... $n are the substrings maching the subpatterns.
		/// Returns the number of replaced occurences.

	static bool match(const std::string& subject, const std::string& pattern, int options = 0);
		/// Matches the given subject string against the regular expression given in pattern,
		/// using the given options.

protected:
	std::string::size_type substOne(std::string& subject, std::string::size_type offset, const std::string& replacement, int options) const;

private:
	pcre*       _pcre;
	pcre_extra* _extra;
	
	static const int OVEC_SIZE;
	
	RegularExpression();
	RegularExpression(const RegularExpression&);
	RegularExpression& operator = (const RegularExpression&);
};


//
// inlines
//
inline int RegularExpression::match(const std::string& subject, Match& mtch, int options) const
{
	return match(subject, 0, mtch, options);
}


inline int RegularExpression::split(const std::string& subject, std::vector<std::string>& strings, int options) const
{
	return split(subject, 0, strings, options);
}


inline int RegularExpression::subst(std::string& subject, const std::string& replacement, int options) const
{
	return subst(subject, 0, replacement, options);
}


} // namespace Poco


#endif // Foundation_RegularExpression_INCLUDED
