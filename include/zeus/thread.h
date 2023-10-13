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
// File: thread.h - Thread support
//

#pragma once

#include <memory>
#include <sys/types.h>
#include <thread>

#include <zeus/message.h>
#include <zeus/private.h>
#include <zeus/signal.h>
#include <zeus/utils.h>

namespace zeus {

class EventDispatcher;
class Message;
class Object;
class ThreadData;
class ThreadMain;

class Thread
{
public:
    Thread();
    virtual ~Thread();

    void start();
    void exit(int code = 0);
    bool wait(utils::duration duration = utils::duration::max());

    bool isRunning();

    Signal<> finished;

    static Thread *current();
    static pid_t currentId();

    EventDispatcher *eventDispatcher();

    void dispatchMessages(Message::Type type = Message::Type::None);

protected:
    int exec();
    virtual void run();

private:
    void startThread();
    void finishThread();

    void postMessage(std::unique_ptr<Message> msg, Object *receiver);
    void removeMessages(Object *receiver);

    friend class Object;
    friend class ThreadData;
    friend class ThreadMain;

    void moveObject(Object *object);
    void moveObject(Object *object, ThreadData *currentData,
                    ThreadData *targetData);

    std::thread thread_;
    ThreadData *data_;
};

} /* namespace zeus */
