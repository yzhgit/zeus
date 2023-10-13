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
// File: event_dispatcher_poll.h - Poll-based event dispatcher
//

#pragma once

#include <list>
#include <map>
#include <vector>

#include <zeus/event_dispatcher.h>
#include <zeus/private.h>
#include <zeus/unique_fd.h>

struct pollfd;

namespace zeus {

class EventNotifier;
class Timer;

class EventDispatcherPoll final : public EventDispatcher
{
public:
    EventDispatcherPoll();
    ~EventDispatcherPoll();

    void registerEventNotifier(EventNotifier *notifier);
    void unregisterEventNotifier(EventNotifier *notifier);

    void registerTimer(Timer *timer);
    void unregisterTimer(Timer *timer);

    void processEvents();
    void interrupt();

private:
    struct EventNotifierSetPoll {
        short events() const;
        EventNotifier *notifiers[3];
    };

    int poll(std::vector<struct pollfd> *pollfds);
    void processInterrupt(const struct pollfd &pfd);
    void processNotifiers(const std::vector<struct pollfd> &pollfds);
    void processTimers();

    std::map<int, EventNotifierSetPoll> notifiers_;
    std::list<Timer *> timers_;
    UniqueFD eventfd_;

    bool processingEvents_;
};

} /* namespace zeus */
