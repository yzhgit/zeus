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
// File: object.h - Base object
//

#pragma once

#include <list>
#include <memory>
#include <vector>

#include <zeus/bound_method.h>

namespace zeus {

class Message;
template<typename... Args>
class Signal;
class SignalBase;
class Thread;

class Object
{
public:
    Object(Object *parent = nullptr);
    virtual ~Object();

    void deleteLater();

    void postMessage(std::unique_ptr<Message> msg);

    template<typename T, typename R, typename... FuncArgs, typename... Args,
             std::enable_if_t<std::is_base_of<Object, T>::value> * = nullptr>
    R invokeMethod(R (T::*func)(FuncArgs...), ConnectionType type,
                   Args &&...args)
    {
        T *obj = static_cast<T *>(this);
        auto *method = new BoundMethodMember<T, R, FuncArgs...>(obj, this, func, type);
        return method->activate(args..., true);
    }

    Thread *thread() const { return thread_; }
    void moveToThread(Thread *thread);

    Object *parent() const { return parent_; }

protected:
    virtual void message(Message *msg);

private:
    friend class SignalBase;
    friend class Thread;

    void notifyThreadMove();

    void connect(SignalBase *signal);
    void disconnect(SignalBase *signal);

    Object *parent_;
    std::vector<Object *> children_;

    Thread *thread_;
    std::list<SignalBase *> signals_;
    unsigned int pendingMessages_;
};

} /* namespace zeus */
