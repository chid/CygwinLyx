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

#ifndef QEVENTDISPATCHER_CYGWIN_P_H
#define QEVENTDISPATCHER_CYGWIN_P_H

//
//  W A R N I N G
//  -------------
//
// This file is not part of the Qt API.  It exists purely as an
// implementation detail.  This header file may change from version to
// version without notice, or even be removed.
//
// We mean it.
//

#include "QtCore/qabstracteventdispatcher.h"
#include "QtCore/qlist.h"
#include "QtCore/qt_windows.h"
#include "private/qabstracteventdispatcher_p.h"
#include "private/qcore_unix_p.h"
#include "private/qpodlist_p.h"
#include "QtCore/qvarlengtharray.h"

#include <sys/time.h>
#include <sys/select.h>

QT_BEGIN_NAMESPACE

// internal timer info
struct QTimerInfo {
    int id;           // - timer identifier
    timeval interval; // - timer interval
    timeval timeout;  // - when to sent event
    QObject *obj;     // - object to receive event
    QTimerInfo **activateRef; // - ref from activateTimers
};

class QTimerInfoList : public QList<QTimerInfo*>
{
#if (_POSIX_MONOTONIC_CLOCK-0 <= 0) || defined(QT_BOOTSTRAPPED)
    timeval previousTime;
    clock_t previousTicks;
    int ticksPerSecond;
    int msPerTick;

    bool timeChanged(timeval *delta);
#endif

    // state variables used by activateTimers()
    QTimerInfo *firstTimerInfo;

    // maximum time to wait for an event
    timeval timer_wait_max;

public:
    QTimerInfoList();

    timeval currentTime;
    timeval updateCurrentTime();

    // must call updateCurrentTime() first!
    void repairTimersIfNeeded();

    bool timerWait(timeval &);
    void timerInsert(QTimerInfo *);
    void timerRepair(const timeval &);

    void registerTimer(int timerId, int interval, QObject *object);
    bool unregisterTimer(int timerId);
    bool unregisterTimers(QObject *object);
    QList<QPair<int, int> > registeredTimers(QObject *object) const;

    int activateTimers();
};

struct QSockNot
{
    QSocketNotifier *obj;
    int fd;
    fd_set *queue;
};

class QSockNotType
{
public:
    QSockNotType();
    ~QSockNotType();

    typedef QPodList<QSockNot*, 32> List;

    List list;
    fd_set select_fds;
    fd_set enabled_fds;
    fd_set pending_fds;

};

class QEventDispatcherCygwinPrivate;

class Q_CORE_EXPORT QEventDispatcherCygwin : public QAbstractEventDispatcher
{
    Q_OBJECT
    Q_DECLARE_PRIVATE(QEventDispatcherCygwin)

public:
    explicit QEventDispatcherCygwin(QObject *parent = 0);
    ~QEventDispatcherCygwin();

    bool processEvents(QEventLoop::ProcessEventsFlags flags);
    bool hasPendingEvents();

    void registerSocketNotifier(QSocketNotifier *notifier);
    void unregisterSocketNotifier(QSocketNotifier *notifier);

    void registerTimer(int timerId, int interval, QObject *object);
    bool unregisterTimer(int timerId);
    bool unregisterTimers(QObject *object);
    QList<TimerInfo> registeredTimers(QObject *object) const;

    void wakeUp();
    void interrupt();
    void flush();

    void startingUp();
    void closingDown();

    bool event(QEvent *e);

protected:
    QEventDispatcherCygwin(QEventDispatcherCygwinPrivate &dd, QObject *parent = 0);

    void setSocketNotifierPending(QSocketNotifier *notifier);

    int activateTimers();
    int activateSocketNotifiers();

    virtual int select(int nfds,
                       fd_set *readfds, fd_set *writefds, fd_set *exceptfds,
                       timeval *timeout);
};

class Q_CORE_EXPORT QEventDispatcherCygwinPrivate : public QAbstractEventDispatcherPrivate
{
    Q_DECLARE_PUBLIC(QEventDispatcherCygwin)

public:
    QEventDispatcherCygwinPrivate();
    ~QEventDispatcherCygwinPrivate();

    int doSelect(QEventLoop::ProcessEventsFlags flags, timeval *timeout);

    bool mainThread;
    int thread_pipe[2];

    // highest fd for all socket notifiers
    int sn_highest;
    // 3 socket notifier types - read, write and exception
    QSockNotType sn_vec[3];

    QTimerInfoList timerList;

    // pending socket notifiers list
    QSockNotType::List sn_pending_list;

    QAtomicInt wakeUps;
    bool interrupt;

    QList<MSG> queuedUserInputEvents;
};

QT_END_NAMESPACE

#endif // QEVENTDISPATCHER_CYGWIN_P_H
