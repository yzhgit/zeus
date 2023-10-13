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
// File: bound_method.cpp - Method bind and invocation
//

#include <zeus/bound_method.h>
#include <zeus/message.h>
#include <zeus/semaphore.h>
#include <zeus/thread.h>

/**
 * \file base/bound_method.h
 * \brief Method bind and invocation
 */

namespace zeus {

/**
 * \enum ConnectionType
 * \brief Connection type for asynchronous communication
 *
 * This enumeration describes the possible types of asynchronous communication
 * between a sender and a receiver. It applies to Signal::emit() and
 * Object::invokeMethod().
 *
 * \var ConnectionTypeAuto
 * \brief If the sender and the receiver live in the same thread,
 * ConnectionTypeDirect is used. Otherwise ConnectionTypeQueued is used.
 *
 * \var ConnectionTypeDirect
 * \brief The receiver is invoked immediately and synchronously in the sender's
 * thread.
 *
 * \var ConnectionTypeQueued
 * \brief The receiver is invoked asynchronously
 *
 * Invoke the receiver asynchronously in its thread when control returns to the
 * thread's event loop. The sender proceeds without waiting for the invocation
 * to complete.
 *
 * \var ConnectionTypeBlocking
 * \brief The receiver is invoked synchronously
 *
 * If the sender and the receiver live in the same thread, this is equivalent to
 * ConnectionTypeDirect. Otherwise, the receiver is invoked asynchronously in
 * its thread when control returns to the thread's event loop. The sender
 * blocks until the receiver signals the completion of the invocation.
 */

/**
 * \brief Invoke the bound method with packed arguments
 * \param[in] pack Packed arguments
 * \param[in] deleteMethod True to delete \a this bound method instance when
 * method invocation completes
 *
 * The bound method stores its return value, if any, in the arguments \a pack.
 * For direct and blocking invocations, this is performed synchronously, and
 * the return value contained in the pack may be used. For queued invocations,
 * the return value is stored at an undefined point of time and shall thus not
 * be used by the caller.
 *
 * \return True if the return value contained in the \a pack may be used by the
 * caller, false otherwise
 */
bool BoundMethodBase::activatePack(std::shared_ptr<BoundMethodPackBase> pack,
                                   bool deleteMethod)
{
    ConnectionType type = connectionType_;
    if (type == ConnectionTypeAuto) {
        if (Thread::current() == object_->thread())
            type = ConnectionTypeDirect;
        else
            type = ConnectionTypeQueued;
    } else if (type == ConnectionTypeBlocking) {
        if (Thread::current() == object_->thread())
            type = ConnectionTypeDirect;
    }

    switch (type) {
    case ConnectionTypeDirect:
    default:
        invokePack(pack.get());
        if (deleteMethod)
            delete this;
        return true;

    case ConnectionTypeQueued: {
        std::unique_ptr<Message> msg =
                std::make_unique<InvokeMessage>(this, pack, nullptr, deleteMethod);
        object_->postMessage(std::move(msg));
        return false;
    }

    case ConnectionTypeBlocking: {
        Semaphore semaphore;

        std::unique_ptr<Message> msg =
                std::make_unique<InvokeMessage>(this, pack, &semaphore, deleteMethod);
        object_->postMessage(std::move(msg));

        semaphore.acquire();
        return true;
    }
    }
}

} /* namespace zeus */
