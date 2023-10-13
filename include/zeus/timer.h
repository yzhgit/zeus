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
// File: timer.h - Generic timer
//

#pragma once

#include <chrono>
#include <stdint.h>

#include <zeus/object.h>
#include <zeus/private.h>
#include <zeus/signal.h>

namespace zeus {

class Message;

class Timer : public Object
{
public:
    Timer(Object *parent = nullptr);
    ~Timer();

    void start(std::chrono::milliseconds duration);
    void start(std::chrono::steady_clock::time_point deadline);
    void stop();
    bool isRunning() const;

    std::chrono::steady_clock::time_point deadline() const { return deadline_; }

    Signal<> timeout;

protected:
    void message(Message *msg) override;

private:
    void registerTimer();
    void unregisterTimer();

    bool running_;
    std::chrono::steady_clock::time_point deadline_;
};

} /* namespace zeus */
