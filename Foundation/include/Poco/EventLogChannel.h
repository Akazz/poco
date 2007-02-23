//
// EventLogChannel.h
//
// $Id: //poco/Main/Foundation/include/Poco/EventLogChannel.h#4 $
//
// Library: Foundation
// Package: Logging
// Module:  EventLogChannel
//
// Definition of the EventLogChannel class specific to WIN32.
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


#ifndef Foundation_EventLogChannel_INCLUDED
#define Foundation_EventLogChannel_INCLUDED


#include "Poco/Foundation.h"
#include "Poco/Channel.h"
#include <windows.h>


namespace Poco {


class Foundation_API EventLogChannel: public Channel
	/// This Windows-only channel works with the Windows NT Event Log
	/// service.
	///
	/// To work properly, the EventLogChannel class requires that either
	/// the PocoFoundation.dll or the PocoMsg.dll Dynamic Link Library
	/// containing the message definition resources can be found in $PATH.
{
public:
	EventLogChannel();
		/// Creates the EventLogChannel.
		/// The name of the current application (or more correctly,
		/// the name of its executable) is taken as event source name.
		
	EventLogChannel(const std::string& name);
		/// Creates the EventLogChannel with the given event source name.
		
	EventLogChannel(const std::string& name, const std::string& host);
		/// Creates an EventLogChannel with the given event source
		/// name that routes messages to the given host.
		
	void open();
		/// Opens the EventLogChannel. If necessary, the
		/// required registry entries to register a
		/// message resource DLL are made.
		
	void close();
		/// Closes the EventLogChannel.
	
	void log(const Message& msg);
		/// Logs the given message to the Windows Event Log.
		///
		/// The message type and priority are mapped to
		/// appropriate values for Event Log type and category.
		
	void setProperty(const std::string& name, const std::string& value);
		/// Sets or changes a configuration property. 
		///
		/// The following properties are supported:
		///
		///   * name:    The name of the event source.
		///   * loghost: The name of the host where the Event Log service is running.
		///              The default is "localhost".
		///   * host:    same as host.
		///   * logfile: The name of the log file. The default is "Application".
		
	std::string getProperty(const std::string& name) const;
		/// Returns the value of the given property.

	static const std::string PROP_NAME;
	static const std::string PROP_HOST;
	static const std::string PROP_LOGHOST;
	static const std::string PROP_LOGFILE;

protected:
	~EventLogChannel();
	static int getType(const Message& msg);
	static int getCategory(const Message& msg);
	void setUpRegistry() const;
#if defined(POCO_WIN32_UTF8)
	static std::wstring findLibrary(const wchar_t* name);
#else
	static std::string findLibrary(const char* name);
#endif

private:
	std::string _name;
	std::string _host;
	std::string _logFile;
	HANDLE      _h;
};


} // namespace Poco


#endif // Foundation_EventLogChannel_INCLUDED
