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
// File: message.h - Message queue support
//

#pragma once

#include <atomic>

#include <zeus/bound_method.h>
#include <zeus/private.h>

namespace zeus {

class BoundMethodBase;
class Object;
class Semaphore;
class Thread;

class Message
{
public:
    enum Type {
        None = 0,
        InvokeMessage = 1,
        ThreadMoveMessage = 2,
        DeferredDelete = 3,
        UserMessage = 1000,
    };

    Message(Type type);
    virtual ~Message();

    Type type() const { return type_; }
    Object *receiver() const { return receiver_; }

    static Type registerMessageType();

private:
    friend class Thread;

    Type type_;
    Object *receiver_;

    static std::atomic_uint nextUserType_;
};

class InvokeMessage : public Message
{
public:
    InvokeMessage(BoundMethodBase *method,
                  std::shared_ptr<BoundMethodPackBase> pack,
                  Semaphore *semaphore = nullptr,
                  bool deleteMethod = false);
    ~InvokeMessage();

    Semaphore *semaphore() const { return semaphore_; }

    void invoke();

private:
    BoundMethodBase *method_;
    std::shared_ptr<BoundMethodPackBase> pack_;
    Semaphore *semaphore_;
    bool deleteMethod_;
};

} /* namespace zeus */
