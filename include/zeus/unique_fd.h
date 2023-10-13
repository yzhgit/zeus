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
// File: unique_fd.h - File descriptor wrapper that owns a file descriptor.
//

#pragma once

#include <utility>

#include <zeus/compiler.h>
#include <zeus/macros.h>

namespace zeus {

class UniqueFD final
{
public:
    UniqueFD()
            : fd_(-1)
    {
    }

    explicit UniqueFD(int fd)
            : fd_(fd)
    {
    }

    UniqueFD(UniqueFD &&other)
            : fd_(other.release())
    {
    }

    ~UniqueFD()
    {
        reset();
    }

    UniqueFD &operator=(UniqueFD &&other)
    {
        reset(other.release());
        return *this;
    }

    __nodiscard int release()
    {
        int fd = fd_;
        fd_ = -1;
        return fd;
    }

    void reset(int fd = -1);

    void swap(UniqueFD &other)
    {
        std::swap(fd_, other.fd_);
    }

    int get() const { return fd_; }
    bool isValid() const { return fd_ >= 0; }

private:
    ZEUS_DISABLE_COPY(UniqueFD)

    int fd_;
};

} /* namespace zeus */
