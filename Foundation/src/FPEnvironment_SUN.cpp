//
// FPEnvironment_SUN.cpp
//
// $Id: //poco/Main/Foundation/src/FPEnvironment_SUN.cpp#9 $
//
// Library: Foundation
// Package: Core
// Module:  FPEnvironment
//
// Copyright (c) 2005-2006, Applied Informatics Software Engineering GmbH.
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


#include <math.h>
#include "Poco/FPEnvironment_SUN.h"


namespace Poco {


FPEnvironmentImpl::FPEnvironmentImpl()
{
	_rnd = fpgetround();
	_exc = fpgetmask();
}


FPEnvironmentImpl::FPEnvironmentImpl(const FPEnvironmentImpl& env)
{
	_rnd = env._rnd;
	_exc = env._exc;
}


FPEnvironmentImpl::~FPEnvironmentImpl()
{
	fpsetround(_rnd);
	fpsetmask(_exc);
}


FPEnvironmentImpl& FPEnvironmentImpl::operator = (const FPEnvironmentImpl& env)
{
	_rnd = env._rnd;
	_exc = env._exc;
	return *this;
}


bool FPEnvironmentImpl::isInfiniteImpl(float value)
{
	int cls = fpclass(value);
	return cls == FP_PINF || cls == FP_NINF;
}


bool FPEnvironmentImpl::isInfiniteImpl(double value)
{
	int cls = fpclass(value);
	return cls == FP_PINF || cls == FP_NINF;
}


bool FPEnvironmentImpl::isInfiniteImpl(long double value)
{
	int cls = fpclass(value);
	return cls == FP_PINF || cls == FP_NINF;
}


bool FPEnvironmentImpl::isNaNImpl(float value)
{
	return isnanf(value) != 0;
}


bool FPEnvironmentImpl::isNaNImpl(double value)
{
	return isnan(value) != 0;
}


bool FPEnvironmentImpl::isNaNImpl(long double value)
{
	return isnan((double) value) != 0;
}


float FPEnvironmentImpl::copySignImpl(float target, float source)
{
	return (float) copysign(target, source);
}


double FPEnvironmentImpl::copySignImpl(double target, double source)
{
	return (float) copysign(target, source);
}


long double FPEnvironmentImpl::copySignImpl(long double target, long double source)
{
	return (source > 0 && target > 0) || (source < 0 && target < 0) ? target : -target;
}


void FPEnvironmentImpl::keepCurrentImpl()
{
	fpsetround(_rnd);
	fpsetmask(_exc);
}


void FPEnvironmentImpl::clearFlagsImpl()
{
	fpsetsticky(0);
}


bool FPEnvironmentImpl::isFlagImpl(FlagImpl flag)
{
	return (fpgetsticky() & flag) != 0;
}


void FPEnvironmentImpl::setRoundingModeImpl(RoundingModeImpl mode)
{
	fpsetround((fp_rnd) mode);
}


FPEnvironmentImpl::RoundingModeImpl FPEnvironmentImpl::getRoundingModeImpl()
{
	return (FPEnvironmentImpl::RoundingModeImpl) fpgetround();
}


} // namespace Poco
