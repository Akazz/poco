//
// Activity.h
//
// $Id: //poco/Main/Foundation/include/Poco/Activity.h#2 $
//
// Library: Foundation
// Package: Threading
// Module:  ActiveObjects
//
// Definition of the Activity template class.
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


#ifndef Foundation_Activity_INCLUDED
#define Foundation_Activity_INCLUDED


#include "Poco/Foundation.h"
#include "Poco/RunnableAdapter.h"
#include "Poco/ThreadPool.h"
#include "Poco/Event.h"
#include "Poco/Mutex.h"


namespace Poco {


template <class C>
class Activity: public Runnable
	/// This template class helps to implement active objects.
	/// An active object uses threads to decouple method
	/// execution from method invocation, or to perform tasks
	/// autonomously, without intervention of a caller.
	///
	/// An activity is a (typically longer running) method
	/// that executes within its own task. Activities can
	/// be started automatically (upon object construction)
	/// or manually at a later time. Activities can also
	/// be stopped at any time. However, to make stopping
	/// an activity work, the method implementing the
	/// activity has to check periodically whether it
	/// has been requested to stop, and if so, return. 
	/// Activities are stopped before the object they belong to is
	/// destroyed. Methods implementing activities cannot have arguments
	/// or return values. 
	///
	/// Activity objects are used as follows:
	///
	///     class ActiveObject
	///     {
	///     public:
	///         ActiveObject(): 
	///             _activity(this, &ActiveObject::runActivity)
	///         {
	///             ...
	///         }
	///   
	///         ...
	///  
	///     protected:
	///         void runActivity()
	///         {
	///             while (!_activity.isStopped())
	///             {
	///                 ...
	///             }
	///         }
	///
	///     private:
	///         Activity<ActiveObject> _activity;
	///     };
{
public:
	typedef RunnableAdapter<C> RunnableAdapterType;
	typedef typename RunnableAdapterType::Callback Callback;

	Activity(C* pOwner, Callback method):
		_pOwner(pOwner),
		_runnable(*pOwner, method),
		_stopped(true),
		_running(false),
		_done(false)
		/// Creates the activity. Call start() to
		/// start it.
	{
		poco_check_ptr (pOwner);
	}
	
	~Activity()
		/// Stops and destroys the activity.
	{
		stop();
		wait();
	}
	
	void start()
		/// Starts the activity by acquiring a
		/// thread for it from the default thread pool.
	{
		FastMutex::ScopedLock lock(_mutex);
		
		if (_stopped)
		{
			_done.reset();
			_stopped = false;
			_running = true;
			try
			{
				ThreadPool::defaultPool().start(*this);
			}
			catch (...)
			{
				_running = false;
				throw;
			}
		}
	}
	
	void stop()
		/// Requests to stop the activity.
	{
		FastMutex::ScopedLock lock(_mutex);

		_stopped = true;
	}
	
	void wait()
		/// Waits for the activity to complete.
	{
		if (_running)
		{
			_done.wait();
		}
	}

	void wait(long milliseconds)
		/// Waits the given interval for the activity to complete.
		/// An TimeoutException is thrown if the activity does not
		/// complete within the given interval.
	{
		if (_running)
		{
			_done.wait(milliseconds);
		}
	}
	
	bool isStopped() const
		/// Returns true if the activity has been requested to stop.
	{
		return _stopped;
	}
	
	bool isRunning() const
		/// Returns true if the activity is running.
	{
		return _running;
	}

protected:
	void run()
	{
		try
		{
			_runnable.run();
		}
		catch (...)
		{
			_running = false;
			_done.set();
			throw;
		}
		_running = false;
		_done.set();
	}
	
private:
	Activity();
	Activity(const Activity&);
	Activity& operator = (const Activity&);

	C*                  _pOwner;
	RunnableAdapterType _runnable;
	volatile bool       _stopped;
	volatile bool       _running;
	Event               _done;
	FastMutex           _mutex;
};


} // namespace Poco


#endif // Foundation_Activity_INCLUDED
