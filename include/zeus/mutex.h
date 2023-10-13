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
// File: mutex.h - Mutex classes with clang thread safety annotation
//

#pragma once

#include <condition_variable>
#include <mutex>

#include <zeus/private.h>
#include <zeus/thread_annotations.h>

namespace zeus {

/* \todo using Mutex = std::mutex if libc++ is used. */

#ifndef __DOXYGEN__

class ZEUS_TSA_CAPABILITY("mutex") Mutex final
{
public:
    constexpr Mutex()
    {
    }

    void lock() ZEUS_TSA_ACQUIRE()
    {
        mutex_.lock();
    }

    void unlock() ZEUS_TSA_RELEASE()
    {
        mutex_.unlock();
    }

private:
    friend class MutexLocker;

    std::mutex mutex_;
};

class ZEUS_TSA_SCOPED_CAPABILITY MutexLocker final
{
public:
    explicit MutexLocker(Mutex &mutex) ZEUS_TSA_ACQUIRE(mutex)
            : lock_(mutex.mutex_)
    {
    }

    MutexLocker(Mutex &mutex, std::defer_lock_t t) noexcept ZEUS_TSA_EXCLUDES(mutex)
            : lock_(mutex.mutex_, t)
    {
    }

    ~MutexLocker() ZEUS_TSA_RELEASE()
    {
    }

    void lock() ZEUS_TSA_ACQUIRE()
    {
        lock_.lock();
    }

    bool try_lock() ZEUS_TSA_TRY_ACQUIRE(true)
    {
        return lock_.try_lock();
    }

    void unlock() ZEUS_TSA_RELEASE()
    {
        lock_.unlock();
    }

private:
    friend class ConditionVariable;

    std::unique_lock<std::mutex> lock_;
};

class ConditionVariable final
{
public:
    ConditionVariable()
    {
    }

    void notify_one() noexcept
    {
        cv_.notify_one();
    }

    void notify_all() noexcept
    {
        cv_.notify_all();
    }

    template<class Predicate>
    void wait(MutexLocker &locker, Predicate stopWaiting)
    {
        cv_.wait(locker.lock_, stopWaiting);
    }

    template<class Rep, class Period, class Predicate>
    bool wait_for(MutexLocker &locker,
                  const std::chrono::duration<Rep, Period> &relTime,
                  Predicate stopWaiting)
    {
        return cv_.wait_for(locker.lock_, relTime, stopWaiting);
    }

private:
    std::condition_variable cv_;
};

#else /* __DOXYGEN__ */

class Mutex final
{
};

class MutexLocker final
{
};

class ConditionVariable final
{
};

#endif /* __DOXYGEN__ */
} /* namespace zeus */
