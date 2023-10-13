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
// File: semaphore.h - General-purpose counting semaphore
//

#pragma once

#include <zeus/mutex.h>
#include <zeus/private.h>

namespace zeus {

class Semaphore
{
public:
    Semaphore(unsigned int n = 0);

    unsigned int available() ZEUS_TSA_EXCLUDES(mutex_);
    void acquire(unsigned int n = 1) ZEUS_TSA_EXCLUDES(mutex_);
    bool tryAcquire(unsigned int n = 1) ZEUS_TSA_EXCLUDES(mutex_);
    void release(unsigned int n = 1) ZEUS_TSA_EXCLUDES(mutex_);

private:
    Mutex mutex_;
    ConditionVariable cv_;
    unsigned int available_ ZEUS_TSA_GUARDED_BY(mutex_);
};

} /* namespace zeus */
