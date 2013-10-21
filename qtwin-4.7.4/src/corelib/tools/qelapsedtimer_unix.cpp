/****************************************************************************
**
** Copyright (C) 2011 Nokia Corporation and/or its subsidiary(-ies).
** All rights reserved.
** Contact: Nokia Corporation (qt-info@nokia.com)
**
** This file is part of the QtCore module of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:LGPL$
** GNU Lesser General Public License Usage
** This file may be used under the terms of the GNU Lesser General Public
** License version 2.1 as published by the Free Software Foundation and
** appearing in the file LICENSE.LGPL included in the packaging of this
** file. Please review the following information to ensure the GNU Lesser
** General Public License version 2.1 requirements will be met:
** http://www.gnu.org/licenses/old-licenses/lgpl-2.1.html.
**
** In addition, as a special exception, Nokia gives you certain additional
** rights. These rights are described in the Nokia Qt LGPL Exception
** version 1.1, included in the file LGPL_EXCEPTION.txt in this package.
**
** GNU General Public License Usage
** Alternatively, this file may be used under the terms of the GNU General
** Public License version 3.0 as published by the Free Software Foundation
** and appearing in the file LICENSE.GPL included in the packaging of this
** file. Please review the following information to ensure the GNU General
** Public License version 3.0 requirements will be met:
** http://www.gnu.org/copyleft/gpl.html.
**
** Other Usage
** Alternatively, this file may be used in accordance with the terms and
** conditions contained in a signed written agreement between you and Nokia.
**
**
**
**
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "qelapsedtimer.h"
#include <sys/time.h>
#include <time.h>
#include <unistd.h>

// Monotonic clocks are supported in Cygwin starting from version 1.7.6.
// Earlier Cygwin versions will use the Windows timers.
#if defined(Q_OS_CYGWIN) && (_POSIX_MONOTONIC_CLOCK-0 == 0)
#define USE_WIN_TIMERS
#endif

#if defined(QT_NO_CLOCK_MONOTONIC) || defined(QT_BOOTSTRAPPED)
// turn off the monotonic clock
# ifdef _POSIX_MONOTONIC_CLOCK
#  undef _POSIX_MONOTONIC_CLOCK
# endif
# define _POSIX_MONOTONIC_CLOCK -1
# undef USE_WIN_TIMERS
#endif

#ifdef USE_WIN_TIMERS
#include "qt_windows.h"
#endif

QT_BEGIN_NAMESPACE

#ifdef USE_WIN_TIMERS
static int monotonicClockChecked = false;
static const bool monotonicClockAvailable = true;
static bool hiresCounter = false;
static qint64 hiresFreq = 0;

// If GetTickCount64() is not available, fall back on GetTickCount()
static quint64 get_tick_count(void) {
    typedef ULONGLONG (WINAPI *PtrGetTickCount64)(void);
    static PtrGetTickCount64 pGetTickCount64 = 0;
    static bool getptr = true;
    if (getptr) {
        HMODULE kernel32 = GetModuleHandleW(L"kernel32");
        if (kernel32) {
            pGetTickCount64 =
                (PtrGetTickCount64)GetProcAddress(kernel32, "GetTickCount64");
        }
        getptr = false;
    }
    if (pGetTickCount64)
        return pGetTickCount64();

    // Use GetTickCount and try to compensate for overflow
    static quint32 highdword = 0;
    static quint32 lastval = 0;
    quint32 val = GetTickCount();
    if (val < lastval)
        ++highdword;
    lastval = val;
    return val | (quint64(highdword) << 32);
}
#elif (_POSIX_MONOTONIC_CLOCK-0 != 0)
static const bool monotonicClockChecked = true;
static const bool monotonicClockAvailable = _POSIX_MONOTONIC_CLOCK > 0;
#else
static int monotonicClockChecked = false;
static int monotonicClockAvailable = false;
#endif

#ifdef Q_CC_GNU
# define is_likely(x) __builtin_expect((x), 1)
#else
# define is_likely(x) (x)
#endif
#define load_acquire(x) ((volatile const int&)(x))
#define store_release(x,v) ((volatile int&)(x) = (v))

static void unixCheckClockType()
{
#if (_POSIX_MONOTONIC_CLOCK-0 == 0)
    if (is_likely(load_acquire(monotonicClockChecked)))
        return;

# ifdef USE_WIN_TIMERS
    LARGE_INTEGER freq;
    if (QueryPerformanceFrequency(&freq)) {
        hiresCounter = true;
        hiresFreq = freq.QuadPart;
    }
# elif defined(_SC_MONOTONIC_CLOCK)
    // detect if the system support monotonic timers
    long x = sysconf(_SC_MONOTONIC_CLOCK);
    store_release(monotonicClockAvailable, x >= 200112L);
# endif

    store_release(monotonicClockChecked, true);
#endif
}

static inline qint64 fractionAdjustment()
{
    // disabled, but otherwise indicates bad usage of QElapsedTimer
    //Q_ASSERT(monotonicClockChecked);

#ifdef USE_WIN_TIMERS
    if (hiresCounter) {
        // the high-resolution timer is measured in microseconds
        // 1 ms = 1000 us
        return 1000;
    } else {
        // ticks are measured in milliseconds
        return 1;
    }
#else
    if (monotonicClockAvailable) {
        // the monotonic timer is measured in nanoseconds
        // 1 ms = 1000000 ns
        return 1000*1000ull;
    } else {
        // gettimeofday is measured in microseconds
        // 1 ms = 1000 us
        return 1000;
    }
#endif
}

bool QElapsedTimer::isMonotonic()
{
    unixCheckClockType();
    return monotonicClockAvailable;
}

QElapsedTimer::ClockType QElapsedTimer::clockType()
{
    unixCheckClockType();
    return monotonicClockAvailable ? MonotonicClock : SystemTime;
}

static inline void do_gettime(qint64 *sec, qint64 *frac)
{
#if (_POSIX_MONOTONIC_CLOCK-0 >= 0)
    unixCheckClockType();
    if (is_likely(monotonicClockAvailable)) {
# ifdef USE_WIN_TIMERS
        if (hiresCounter) {
            LARGE_INTEGER hires;
            QueryPerformanceCounter(&hires);
            *sec = hires.QuadPart / hiresFreq;
            *frac = ((hires.QuadPart % hiresFreq) * 1000000) / hiresFreq;
        } else {
            // If a hires counter is not available, use GetTickCount64 (if
            // available) or GetTickCount, which are unaffected by clock skew.
            // Warning! GetTickCount64 is only available starting from Vista.
            // If GetTickCount is used, the time will wrap around to zero every
            // about 49.7 days if the system is run continuously. This overflow
            // is accounted for, but different processes may have different
            // understanding of how much time has actually elapsed.
            quint64 lores = get_tick_count();
            *sec = lores / 1000;
            *frac = lores % 1000;
        }
# else
        timespec ts;
        clock_gettime(CLOCK_MONOTONIC, &ts);
        *sec = ts.tv_sec;
        *frac = ts.tv_nsec;
# endif
        return;
    }
#endif
    // use gettimeofday
    timeval tv;
    ::gettimeofday(&tv, 0);
    *sec = tv.tv_sec;
    *frac = tv.tv_usec;
}

// used in qcore_unix.cpp and qeventdispatcher_unix.cpp
timeval qt_gettime()
{
    qint64 sec, frac;
    do_gettime(&sec, &frac);

    timeval tv;
    tv.tv_sec = sec;
    tv.tv_usec = frac;
#ifdef USE_WIN_TIMERS
    if (!hiresCounter)
        tv.tv_usec *= 1000;
#else
    if (monotonicClockAvailable)
        tv.tv_usec /= 1000;
#endif

    return tv;
}

static qint64 elapsedAndRestart(qint64 sec, qint64 frac,
                                qint64 *nowsec, qint64 *nowfrac)
{
    do_gettime(nowsec, nowfrac);
    sec = *nowsec - sec;
    frac = *nowfrac - frac;
    return sec * Q_INT64_C(1000) + frac / fractionAdjustment();
}

void QElapsedTimer::start()
{
    do_gettime(&t1, &t2);
}

qint64 QElapsedTimer::restart()
{
    return elapsedAndRestart(t1, t2, &t1, &t2);
}

qint64 QElapsedTimer::elapsed() const
{
    qint64 sec, frac;
    return elapsedAndRestart(t1, t2, &sec, &frac);
}

qint64 QElapsedTimer::msecsSinceReference() const
{
    return t1 * Q_INT64_C(1000) + t2 / fractionAdjustment();
}

qint64 QElapsedTimer::msecsTo(const QElapsedTimer &other) const
{
    qint64 secs = other.t1 - t1;
    qint64 fraction = other.t2 - t2;
    return secs * Q_INT64_C(1000) + fraction / fractionAdjustment();
}

qint64 QElapsedTimer::secsTo(const QElapsedTimer &other) const
{
    return other.t1 - t1;
}

bool operator<(const QElapsedTimer &v1, const QElapsedTimer &v2)
{
    return v1.t1 < v2.t1 || (v1.t1 == v2.t1 && v1.t2 < v2.t2);
}

QT_END_NAMESPACE
