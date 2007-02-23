//
// TaskNotification.h
//
// $Id: //poco/Main/Foundation/include/Poco/TaskNotification.h#3 $
//
// Library: Foundation
// Package: Tasks
// Module:  Tasks
//
// Definition of the TaskNotification class.
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


#ifndef Foundation_TaskNotification_INCLUDED
#define Foundation_TaskNotification_INCLUDED


#include "Poco/Foundation.h"
#include "Poco/Notification.h"
#include "Poco/Task.h"


namespace Poco {


class Foundation_API TaskNotification: public Notification
	/// Base class for TaskManager notifications.
{
public:
	TaskNotification(Task* pTask);
		/// Creates the TaskNotification.

	Task* task() const;
		/// Returns the subject of the notification.

protected:
	virtual ~TaskNotification();
		/// Destroys the TaskNotification.

private:
	Task* _pTask;
};


class Foundation_API TaskStartedNotification: public TaskNotification
	/// This notification is posted by the TaskManager for
	/// every task that has been started.
{
public:
	TaskStartedNotification(Task* pTask);
	
protected:
	~TaskStartedNotification();
};


class Foundation_API TaskCancelledNotification: public TaskNotification
	/// This notification is posted by the TaskManager for
	/// every task that has been cancelled.
{
public:
	TaskCancelledNotification(Task* pTask);

protected:
	~TaskCancelledNotification();
};


class Foundation_API TaskFinishedNotification: public TaskNotification
	/// This notification is posted by the TaskManager for
	/// every task that has finished.
{
public:
	TaskFinishedNotification(Task* pTask);

protected:
	~TaskFinishedNotification();
};


class Foundation_API TaskFailedNotification: public TaskNotification
	/// This notification is posted by the TaskManager for
	/// every task that has failed with an exception.
{
public:
	TaskFailedNotification(Task* pTask, const Exception& exc);

	const Exception& reason() const;

protected:
	~TaskFailedNotification();
	
private:
	Exception* _pException;
};


class Foundation_API TaskProgressNotification: public TaskNotification
	/// This notification is posted by the TaskManager for
	/// every task that has failed with an exception.
{
public:
	TaskProgressNotification(Task* pTask, float progress);

	float progress() const;

protected:
	~TaskProgressNotification();
	
private:
	float _progress;
};


template <class C>
class TaskCustomNotification: public TaskNotification
	/// This is a template for "custom" notification.
	/// Unlike other notifications, this notification
	/// is instantiated and posted by the task itself.
	/// The purpose is to provide generic notifiation
	/// mechanism between the task and its observer(s).
{
public:
	TaskCustomNotification(Task* pTask, const C& custom):
		TaskNotification(pTask),
		_custom(custom)
	{
	}

	const C& custom() const
	{
		return _custom;
	}

protected:
	~TaskCustomNotification(){};
	
private:
	C _custom;
};


//
// inlines
//
inline Task* TaskNotification::task() const
{
	return _pTask;
}


inline const Exception& TaskFailedNotification::reason() const
{
	return *_pException;
}


inline float TaskProgressNotification::progress() const
{
	return _progress;
}


} // namespace Poco


#endif // Foundation_TaskNotification_INCLUDED
