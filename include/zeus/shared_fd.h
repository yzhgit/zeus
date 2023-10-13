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
// File: shared_fd.h - File descriptor wrapper with shared ownership
//

#pragma once

#include <memory>

namespace zeus {

class UniqueFD;

class SharedFD final
{
public:
    explicit SharedFD(const int &fd = -1);
    explicit SharedFD(int &&fd);
    explicit SharedFD(UniqueFD fd);
    SharedFD(const SharedFD &other);
    SharedFD(SharedFD &&other);
    ~SharedFD();

    SharedFD &operator=(const SharedFD &other);
    SharedFD &operator=(SharedFD &&other);

    bool isValid() const { return fd_ != nullptr; }
    int get() const { return fd_ ? fd_->fd() : -1; }
    UniqueFD dup() const;

private:
    class Descriptor
    {
    public:
        Descriptor(int fd, bool duplicate);
        ~Descriptor();

        int fd() const { return fd_; }

    private:
        int fd_;
    };

    std::shared_ptr<Descriptor> fd_;
};

static inline bool operator==(const SharedFD &lhs, const SharedFD &rhs)
{
    return lhs.get() == rhs.get();
}

static inline bool operator!=(const SharedFD &lhs, const SharedFD &rhs)
{
    return !(lhs == rhs);
}

} /* namespace zeus */
