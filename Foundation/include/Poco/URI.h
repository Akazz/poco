//
// URI.h
//
// $Id: //poco/Main/Foundation/include/Poco/URI.h#2 $
//
// Library: Foundation
// Package: URI
// Module:  URI
//
// Definition of the URI class.
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


#ifndef Foundation_URI_INCLUDED
#define Foundation_URI_INCLUDED


#include "Poco/Foundation.h"
#include <vector>


namespace Poco {


class Foundation_API URI
	/// A Uniform Resource Identifier, as specified in RFC 3986.
	/// 
	/// The URI class provides methods for building URIs from their
	/// parts, as well as for splitting URIs into their parts.
	/// Furthermore, the class provides methods for resolving
	/// relative URIs against base URIs.
	///
	/// The class automatically performs a few normalizations on
	/// all URIs and URI parts passed to it:
	///   * scheme identifiers are converted to lower case.
	///   * percent-encoded characters are decoded
	///   * optionally, dot segments are removed from paths (see normalize())
{
public:
	URI();
		/// Creates an empty URI.

	explicit URI(const std::string& uri);
		/// Parses an URI from the given string. Throws a
		/// SyntaxException if the uri is not valid.
		
	explicit URI(const char* uri);
		/// Parses an URI from the given string. Throws a
		/// SyntaxException if the uri is not valid.
		
	URI(const std::string& scheme, const std::string& pathEtc);
		/// Creates an URI from its parts.
		
	URI(const std::string& scheme, const std::string& authority, const std::string& pathEtc);
		/// Creates an URI from its parts.

	URI(const std::string& scheme, const std::string& authority, const std::string& path, const std::string& query);
		/// Creates an URI from its parts.

	URI(const std::string& scheme, const std::string& authority, const std::string& path, const std::string& query, const std::string& fragment);
		/// Creates an URI from its parts.

	URI(const URI& uri);
		/// Copy constructor. Creates an URI from another one.
		
	URI(const URI& baseURI, const std::string& relativeURI);
		/// Creates an URI from a base URI and a relative URI, according to
		/// the algorithm in section 5.2 of RFC 3986.

	~URI();
		/// Destroys the URI.
	
	URI& operator = (const URI& uri);
		/// Assignment operator.
		
	URI& operator = (const std::string& uri);
		/// Parses and assigns an URI from the given string. Throws a
		/// SyntaxException if the uri is not valid.

	URI& operator = (const char* uri);
		/// Parses and assigns an URI from the given string. Throws a
		/// SyntaxException if the uri is not valid.
		
	void swap(URI& uri);
		/// Swaps the URI with another one.	
		
	void clear();
		/// Clears all parts of the URI.
	
	std::string toString() const;
		/// Returns a string representation of the URI.
		///
		/// Characters in the path, query and fragment parts will be 
		/// percent-encoded as necessary.
	
	const std::string& getScheme() const;
		/// Returns the scheme part of the URI.
		
	void setScheme(const std::string& scheme);
		/// Sets the scheme part of the URI. The given scheme
		/// is converted to lower-case.
		///
		/// A list of registered URI schemes can be found
		/// at <http://www.iana.org/assignments/uri-schemes>.
		
	const std::string& getUserInfo() const;
		/// Returns the user-info part of the URI.
		
	void setUserInfo(const std::string& userInfo);
		/// Sets the user-info part of the URI.
		
	const std::string& getHost() const;
		/// Returns the host part of the URI.
		
	void setHost(const std::string& host);
		/// Sets the host part of the URI.
		
	unsigned short getPort() const;
		/// Returns the port number part of the URI.
		///
		/// If no port number (0) has been specified, the
		/// well-known port number (e.g., 80 for http) for
		/// the given scheme is returned if it is known.
		/// Otherwise, 0 is returned.
		
	void setPort(unsigned short port);
		/// Sets the port number part of the URI.
		
	std::string getAuthority() const;
		/// Returns the authority part (userInfo, host and port)
		/// of the URI. 
		///
		/// If the port number is a well-known port
		/// number for the given scheme (e.g., 80 for http), it
		/// is not included in the authority.
		
	void setAuthority(const std::string& authority);
		/// Parses the given authority part for the URI and sets
		/// the user-info, host, port components accordingly.
		
	const std::string& getPath() const;
		/// Returns the path part of the URI.
		
	void setPath(const std::string& path);
		/// Sets the path part of the URI.
	
	std::string getQuery() const;
		/// Returns the query part of the URI.
		
	void setQuery(const std::string& query);	
		/// Sets the query part of the URI.

	const std::string& getRawQuery() const;
		/// Returns the unencoded query part of the URI.
		
	void setRawQuery(const std::string& query);	
		/// Sets the query part of the URI.
	
	const std::string& getFragment() const;
		/// Returns the fragment part of the URI.
		
	void setFragment(const std::string& fragment);
		/// Sets the fragment part of the URI.
		
	void setPathEtc(const std::string& pathEtc);
		/// Sets the path, query and fragment parts of the URI.
		
	std::string getPathEtc() const;
		/// Returns the path, query and fragment parts of the URI.
		
	std::string getPathAndQuery() const;
		/// Returns the path and query parts of the URI.	
		
	void resolve(const std::string& relativeURI);
		/// Resolves the given relative URI against the base URI.
		/// See section 5.2 of RFC 3986 for the algorithm used.

	void resolve(const URI& relativeURI);
		/// Resolves the given relative URI against the base URI.
		/// See section 5.2 of RFC 3986 for the algorithm used.

	bool isRelative() const;
		/// Returns true if the URI is a relative reference, false otherwise.
		///
		/// A relative reference does not contain a scheme identifier.
		/// Relative references are usually resolved against an absolute
		/// base reference.
	
	bool empty() const;
		/// Returns true if the URI is empty, false otherwise.
		
	bool operator == (const URI& uri) const;
		/// Returns true if both URIs are identical, false otherwise.
		///
		/// Two URIs are identical if their scheme, authority,
		/// path, query and fragment part are identical.

	bool operator == (const std::string& uri) const;
		/// Parses the given URI and returns true if both URIs are identical,
		/// false otherwise.

	bool operator != (const URI& uri) const;
		/// Returns true if both URIs are identical, false otherwise.

	bool operator != (const std::string& uri) const;
		/// Parses the given URI and returns true if both URIs are identical,
		/// false otherwise.
		
	void normalize();
		/// Normalizes the URI by removing all but leading . and .. segments from the path.
		///
		/// If the first path segment in a relative path contains a colon (:), 
		/// such as in a Windows path containing a drive letter, a dot segment (./) 
		/// is prepended in accordance with section 3.3 of RFC 3986.
	
	void getPathSegments(std::vector<std::string>& segments);
		/// Places the single path segments (delimited by slashes) into the
		/// given vector.
	
	static void encode(const std::string& str, const std::string& reserved, std::string& encodedStr);
		/// URI-encodes the given string by escaping reserved and non-ASCII
		/// characters. The encoded string is appended to encodedStr.
		
	static void decode(const std::string& str, std::string& decodedStr);
		/// URI-decodes the given string by replacing percent-encoded
		/// characters with the actual character. The decoded string
		/// is appended to decodedStr.

protected:
	bool equals(const URI& uri) const;
		/// Returns true if both uri's are equivalent.
	
	bool isWellKnownPort() const;
		/// Returns true if the URI's port number is a well-known one
		/// (for example, 80, if the scheme is http).
		
	unsigned short getWellKnownPort() const;
		/// Returns the well-known port number for the URI's scheme,
		/// or 0 if the port number is not known.
		
	void parse(const std::string& uri);
		/// Parses and assigns an URI from the given string. Throws a
		/// SyntaxException if the uri is not valid.

	void parseAuthority(std::string::const_iterator& it, const std::string::const_iterator& end);
		/// Parses and sets the user-info, host and port from the given data.

	void parseHostAndPort(std::string::const_iterator& it, const std::string::const_iterator& end);
		/// Parses and sets the host and port from the given data.

	void parsePath(std::string::const_iterator& it, const std::string::const_iterator& end);
		/// Parses and sets the path from the given data.

	void parsePathEtc(std::string::const_iterator& it, const std::string::const_iterator& end);
		/// Parses and sets the path, query and fragment from the given data.

	void parseQuery(std::string::const_iterator& it, const std::string::const_iterator& end);
		/// Parses and sets the query from the given data.

	void parseFragment(std::string::const_iterator& it, const std::string::const_iterator& end);
		/// Parses and sets the fragment from the given data.

	void mergePath(const std::string& path);
		/// Appends a path to the URI's path.

	void removeDotSegments(bool removeLeading = true);
		/// Removes all dot segments from the path.

	static void getPathSegments(const std::string& path, std::vector<std::string>& segments);
		/// Places the single path segments (delimited by slashes) into the
		/// given vector.

	void buildPath(const std::vector<std::string>& segments, bool leadingSlash, bool trailingSlash);
		/// Builds the path from the given segments.

	static const std::string RESERVED_PATH;
	static const std::string RESERVED_QUERY;
	static const std::string RESERVED_FRAGMENT;
	static const std::string ILLEGAL;
	
private:
	std::string    _scheme;
	std::string    _userInfo;
	std::string    _host;
	unsigned short _port;
	std::string    _path;
	std::string    _query;
	std::string    _fragment;
};


//
// inlines
//
inline const std::string& URI::getScheme() const
{
	return _scheme;
}
	

inline const std::string& URI::getUserInfo() const
{
	return _userInfo;
}

	
inline const std::string& URI::getHost() const
{
	return _host;
}

	
inline const std::string& URI::getPath() const
{
	return _path;
}

	
inline const std::string& URI::getRawQuery() const
{
	return _query;
}

	
inline const std::string& URI::getFragment() const
{
	return _fragment;
}


inline void swap(URI& u1, URI& u2)
{
	u1.swap(u2);
}

	
} // namespace Poco


#endif // Foundation_URI_INCLUDED
