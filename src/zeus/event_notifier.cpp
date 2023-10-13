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
// File: event_notifier.cpp - File descriptor event notifier
//

#include <zeus/event_dispatcher.h>
#include <zeus/event_notifier.h>
#include <zeus/message.h>
#include <zeus/thread.h>

// #include <zeus/common/camera_manager.h>

/**
 * \file event_notifier.h
 * \brief File descriptor event notifier
 */

namespace zeus {

/**
 * \class EventNotifier
 * \brief Notify of activity on a file descriptor
 *
 * The EventNotifier models a file descriptor event source that can be
 * monitored. It is created with the file descriptor to be monitored and the
 * type of event, and is enabled by default. It will emit the \ref activated
 * signal whenever an event of the monitored type occurs on the file descriptor.
 *
 * Supported type of events are EventNotifier::Read, EventNotifier::Write and
 * EventNotifier::Exception. The type is specified when constructing the
 * notifier, and can be retrieved using the type() function. To listen to
 * multiple event types on the same file descriptor multiple notifiers must be
 * created.
 *
 * The notifier can be disabled with the setEnabled() function. When the notifier
 * is disabled it ignores events and does not emit the \ref activated signal.
 * The notifier can then be re-enabled with the setEnabled() function.
 *
 * Creating multiple notifiers of the same type for the same file descriptor is
 * not allowed and results in undefined behaviour.
 *
 * Notifier events are detected and dispatched from the
 * EventDispatcher::processEvents() function.
 */

/**
 * \enum EventNotifier::Type
 * Type of file descriptor event to listen for.
 * \var EventNotifier::Read
 * Data is available to be read from the file descriptor
 * \var EventNotifier::Write
 * Data can be written to the file descriptor
 * \var EventNotifier::Exception
 * An exception has occurred on the file descriptor
 */

/**
 * \brief Construct an event notifier with a file descriptor and event type
 * \param[in] fd The file descriptor to monitor
 * \param[in] type The event type to monitor
 * \param[in] parent The parent Object
 */
EventNotifier::EventNotifier(int fd, Type type, Object *parent)
        : Object(parent), fd_(fd), type_(type), enabled_(false)
{
    setEnabled(true);
}

EventNotifier::~EventNotifier()
{
    setEnabled(false);
}

/**
 * \fn EventNotifier::type()
 * \brief Retrieve the type of the event being monitored
 * \return The type of the event
 */

/**
 * \fn EventNotifier::fd()
 * \brief Retrieve the file descriptor being monitored
 * \return The file descriptor
 */

/**
 * \fn EventNotifier::enabled()
 * \brief Retrieve the notifier state
 * \return True if the notifier is enabled, or false otherwise
 * \sa setEnabled()
 */

/**
 * \brief Enable or disable the notifier
 * \param[in] enable True to enable the notifier, false to disable it
 *
 * This function enables or disables the notifier. A disabled notifier ignores
 * events and does not emit the \ref activated signal.
 *
 * \context This function is \threadbound.
 */
void EventNotifier::setEnabled(bool enable)
{
    if (enabled_ == enable)
        return;

    enabled_ = enable;

    EventDispatcher *dispatcher = thread()->eventDispatcher();
    if (enable)
        dispatcher->registerEventNotifier(this);
    else
        dispatcher->unregisterEventNotifier(this);
}

/**
 * \var EventNotifier::activated
 * \brief Signal emitted when the event occurs
 *
 * This signal is emitted when the event \ref type() occurs on the file
 * descriptor monitored by the notifier. The notifier pointer is passed as a
 * parameter.
 */

void EventNotifier::message(Message *msg)
{
    if (msg->type() == Message::ThreadMoveMessage) {
        if (enabled_) {
            setEnabled(false);
            invokeMethod(&EventNotifier::setEnabled,
                         ConnectionTypeQueued, true);
        }
    }

    Object::message(msg);
}

} /* namespace zeus */
