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
// File: unique_fd.cpp - File descriptor wrapper that owns a file descriptor
//

#include <unistd.h>
#include <utility>

#include <zeus/log.h>
#include <zeus/unique_fd.h>

/**
 * \file base/unique_fd.h
 * \brief File descriptor wrapper that owns a file descriptor
 */

namespace zeus {

LOG_DEFINE_CATEGORY(UniqueFD)

/**
 * \class UniqueFD
 * \brief unique_ptr-like wrapper for a file descriptor
 *
 * The UniqueFD is a wrapper that owns and manages the lifetime of a file
 * descriptor. It is constructed from a numerical file descriptor, and takes
 * over its ownership. The file descriptor is closed when the UniqueFD is
 * destroyed, or when it is assigned another file descriptor with operator=()
 * or reset().
 */

/**
 * \fn UniqueFD::UniqueFD()
 * \brief Construct a UniqueFD that owns no file descriptor
 */

/**
 * \fn UniqueFD::UniqueFD(int fd)
 * \brief Construct a UniqueFD that owns \a fd
 * \param[in] fd A file descriptor to manage
 */

/**
 * \fn UniqueFD::UniqueFD(UniqueFD &&other)
 * \brief Move constructor, create a UniqueFD by taking over \a other
 * \param[in] other The other UniqueFD
 *
 * Create a UniqueFD by transferring ownership of the file descriptor owned by
 * \a other. Upon return, the \a other UniqueFD is invalid.
 */

/**
 * \fn UniqueFD::~UniqueFD()
 * \brief Destroy the UniqueFD instance
 *
 * If a file descriptor is owned, it is closed.
 */

/**
 * \fn UniqueFD::operator=(UniqueFD &&other)
 * \brief Move assignment operator, replace a UniqueFD by taking over \a other
 * \param[in] other The other UniqueFD
 *
 * If this UniqueFD owns a file descriptor, the file descriptor is closed
 * first. The file descriptor is then replaced by the one of \a other. Upon
 * return, \a other is invalid.
 *
 * \return A reference to this UniqueFD
 */

/**
 * \fn UniqueFD::release()
 * \brief Release ownership of the file descriptor without closing it
 *
 * This function releases and returns the owned file descriptor without closing
 * it. The caller owns the returned value and must take care of handling its
 * life time to avoid file descriptor leakages. Upon return this UniqueFD is
 * invalid.
 *
 * \return The managed file descriptor, or -1 if no file descriptor was owned
 */

/**
 * \brief Replace the managed file descriptor
 * \param[in] fd The new file descriptor to manage
 *
 * Close the managed file descriptor, if any, and replace it with the new \a fd.
 *
 * Self-resetting (passing an \a fd already managed by this instance) is invalid
 * and results in undefined behaviour.
 */
void UniqueFD::reset(int fd)
{
    ASSERT(!isValid() || fd != fd_);

    std::swap(fd, fd_);

    if (fd >= 0)
        close(fd);
}

/**
 * \fn UniqueFD::swap(UniqueFD &other)
 * \brief Swap the managed file descriptors with another UniqueFD
 * \param[in] other Another UniqueFD to swap the file descriptor with
 */

/**
 * \fn UniqueFD::get()
 * \brief Retrieve the managed file descriptor
 * \return The managed file descriptor, or -1 if no file descriptor is owned
 */

/**
 * \fn UniqueFD::isValid()
 * \brief Check if the UniqueFD owns a valid file descriptor
 * \return True if the UniqueFD owns a valid file descriptor, false otherwise
 */

} /* namespace zeus */
