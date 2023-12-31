// Copyright 2017 The Abseil Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// Copyright 2017 The Abseil Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// File: timer.cpp - Generic timer
//

#include <chrono>

#include <zeus/event_dispatcher.h>
#include <zeus/log.h>
#include <zeus/message.h>
#include <zeus/thread.h>
#include <zeus/timer.h>
#include <zeus/utils.h>

// #include <zeus/common/camera_manager.h>

/**
 * \file base/timer.h
 * \brief Generic timer
 */

namespace zeus {

LOG_DEFINE_CATEGORY(Timer)

/**
 * \class Timer
 * \brief Single-shot timer interface
 *
 * The Timer class models a single-shot timer that is started with start() and
 * emits the \ref timeout signal when it times out.
 *
 * Once started the timer will run until it times out. It can be stopped with
 * stop(), and once it times out or is stopped, can be started again with
 * start().
 *
 * The timer deadline is specified as either a duration in milliseconds or an
 * absolute time point. If the deadline is set to the current time or to the
 * past, the timer will time out immediately when execution returns to the
 * event loop of the timer's thread.
 *
 * Timers run in the thread they belong to, and thus emit the \a ref timeout
 * signal from that thread. To avoid race conditions they must not be started
 * or stopped from a different thread, attempts to do so will be rejected and
 * logged, and may cause undefined behaviour.
 */

/**
 * \brief Construct a timer
 * \param[in] parent The parent Object
 */
Timer::Timer(Object *parent)
        : Object(parent), running_(false)
{
}

Timer::~Timer()
{
    stop();
}

/**
 * \brief Start or restart the timer with a timeout of \a duration
 * \param[in] duration The timer duration in milliseconds
 *
 * If the timer is already running it will be stopped and restarted.
 *
 * \context This function is \threadbound.
 */
void Timer::start(std::chrono::milliseconds duration)
{
    start(utils::clock::now() + duration);
}

/**
 * \brief Start or restart the timer with a \a deadline
 * \param[in] deadline The timer deadline
 *
 * If the timer is already running it will be stopped and restarted.
 *
 * \context This function is \threadbound.
 */
void Timer::start(std::chrono::steady_clock::time_point deadline)
{
    if (Thread::current() != thread()) {
        LOG(Timer, Error) << "Timer " << this << " << can't be started from another thread";
        return;
    }

    deadline_ = deadline;

    LOG(Timer, Debug)
            << "Starting timer " << this << ": deadline "
            << utils::time_point_to_string(deadline_);

    if (isRunning())
        unregisterTimer();

    registerTimer();
}

/**
 * \brief Stop the timer
 *
 * After this function returns the timer is guaranteed not to emit the
 * \ref timeout signal.
 *
 * If the timer is not running this function performs no operation.
 *
 * \context This function is \threadbound.
 */
void Timer::stop()
{
    if (!isRunning())
        return;

    if (Thread::current() != thread()) {
        LOG(Timer, Error) << "Timer " << this << " can't be stopped from another thread";
        return;
    }

    unregisterTimer();
}

void Timer::registerTimer()
{
    thread()->eventDispatcher()->registerTimer(this);
    running_ = true;
}

void Timer::unregisterTimer()
{
    running_ = false;
    thread()->eventDispatcher()->unregisterTimer(this);
}

/**
 * \brief Check if the timer is running
 * \return True if the timer is running, false otherwise
 */
bool Timer::isRunning() const
{
    return running_;
}

/**
 * \fn Timer::deadline()
 * \brief Retrieve the timer deadline
 * \return The timer deadline
 */

/**
 * \var Timer::timeout
 * \brief Signal emitted when the timer times out
 *
 * The timer pointer is passed as a parameter.
 */

void Timer::message(Message *msg)
{
    if (msg->type() == Message::ThreadMoveMessage) {
        if (isRunning()) {
            unregisterTimer();
            invokeMethod(&Timer::registerTimer,
                         ConnectionTypeQueued);
        }
    }

    Object::message(msg);
}

} /* namespace zeus */
