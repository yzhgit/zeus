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
// File: event_notifier.h - File descriptor event notifier
//

#pragma once

#include <zeus/object.h>
#include <zeus/private.h>
#include <zeus/signal.h>

namespace zeus {

class Message;

class EventNotifier : public Object
{
public:
    enum Type {
        Read,
        Write,
        Exception,
    };

    EventNotifier(int fd, Type type, Object *parent = nullptr);
    virtual ~EventNotifier();

    Type type() const { return type_; }
    int fd() const { return fd_; }

    bool enabled() const { return enabled_; }
    void setEnabled(bool enable);

    Signal<> activated;

protected:
    void message(Message *msg) override;

private:
    int fd_;
    Type type_;
    bool enabled_;
};

} /* namespace zeus */
