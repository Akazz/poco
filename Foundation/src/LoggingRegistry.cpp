//
// LoggingRegistry.cpp
//
// $Id: //poco/Main/Foundation/src/LoggingRegistry.cpp#7 $
//
// Library: Foundation
// Package: Logging
// Module:  LoggingRegistry
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


#include "Poco/LoggingRegistry.h"
#include "Poco/SingletonHolder.h"


namespace Poco {


LoggingRegistry::LoggingRegistry()
{
}


LoggingRegistry::~LoggingRegistry()
{
}


Channel* LoggingRegistry::channelForName(const std::string& name) const
{
	FastMutex::ScopedLock lock(_mutex);
	
	ChannelMap::const_iterator it = _channelMap.find(name);
	if (it != _channelMap.end())
		return const_cast<Channel*>(it->second.get());
	else
		throw NotFoundException("logging channel", name);
}


Formatter* LoggingRegistry::formatterForName(const std::string& name) const
{
	FastMutex::ScopedLock lock(_mutex);

	FormatterMap::const_iterator it = _formatterMap.find(name);
	if (it != _formatterMap.end())
		return const_cast<Formatter*>(it->second.get());
	else
		throw NotFoundException("logging formatter", name);
}


void LoggingRegistry::registerChannel(const std::string& name, Channel* pChannel)
{
	FastMutex::ScopedLock lock(_mutex);

	_channelMap[name] = ChannelPtr(pChannel, true);
}

	
void LoggingRegistry::registerFormatter(const std::string& name, Formatter* pFormatter)
{
	FastMutex::ScopedLock lock(_mutex);

	_formatterMap[name] = FormatterPtr(pFormatter, true);
}


void LoggingRegistry::unregisterChannel(const std::string& name)
{
	FastMutex::ScopedLock lock(_mutex);

	ChannelMap::iterator it = _channelMap.find(name);
	if (it != _channelMap.end())
		_channelMap.erase(it);
	else
		throw NotFoundException("logging channel", name);
}


void LoggingRegistry::unregisterFormatter(const std::string& name)
{
	FastMutex::ScopedLock lock(_mutex);

	FormatterMap::iterator it = _formatterMap.find(name);
	if (it != _formatterMap.end())
		_formatterMap.erase(it);
	else
		throw NotFoundException("logging formatter", name);
}


void LoggingRegistry::clear()
{
	FastMutex::ScopedLock lock(_mutex);

	_channelMap.clear();
	_formatterMap.clear();
}


LoggingRegistry& LoggingRegistry::defaultRegistry()
{
	static SingletonHolder<LoggingRegistry> sh;
	return *sh.get();
}


} // namespace Poco
