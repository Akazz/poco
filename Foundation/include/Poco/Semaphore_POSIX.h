//
// Semaphore_POSIX.h
//
// $Id: //poco/Main/Foundation/include/Poco/Semaphore_POSIX.h#2 $
//
// Library: Foundation
// Package: Threading
// Module:  Semaphore
//
// Definition of the SemaphoreImpl class for POSIX Threads.
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


#ifndef Foundation_Semaphore_POSIX_INCLUDED
#define Foundation_Semaphore_POSIX_INCLUDED


#include "Poco/Foundation.h"
#include "Poco/Exception.h"
#include <pthread.h>
#include <errno.h>


namespace Poco {


class Foundation_API SemaphoreImpl
{
protected:
	SemaphoreImpl(int n, int max);		
	~SemaphoreImpl();
	void setImpl();
	void waitImpl();
	bool waitImpl(long milliseconds);
	
private:
	volatile int    _n;
	int             _max;
	pthread_mutex_t _mutex;
	pthread_cond_t  _cond;
};


//
// inlines
//
inline void SemaphoreImpl::setImpl()
{
	if (pthread_mutex_lock(&_mutex))	
		throw SystemException("cannot signal semaphore (lock)");
	if (_n < _max)
	{
		++_n;
	}
	else
	{
		pthread_mutex_unlock(&_mutex);
		throw SystemException("cannot signal semaphore: count would exceed maximum");
	}	
	if (pthread_cond_signal(&_cond))
	{
		pthread_mutex_unlock(&_mutex);
		throw SystemException("cannot signal semaphore");
	}
	pthread_mutex_unlock(&_mutex);
}


} // namespace Poco


#endif // Foundation_Semaphore_POSIX_INCLUDED
