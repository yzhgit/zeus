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
// File: file.h - File I/O operations
//

#pragma once

#include <map>
#include <string>
#include <sys/types.h>

#include <zeus/flags.h>
#include <zeus/macros.h>
#include <zeus/private.h>
#include <zeus/span.h>
#include <zeus/unique_fd.h>

namespace zeus {

class File
{
public:
    enum class MapFlag {
        NoOption = 0,
        Private = (1 << 0),
    };

    using MapFlags = Flags<MapFlag>;

    enum class OpenModeFlag {
        NotOpen = 0,
        ReadOnly = (1 << 0),
        WriteOnly = (1 << 1),
        ReadWrite = ReadOnly | WriteOnly,
    };

    using OpenMode = Flags<OpenModeFlag>;

    File(const std::string &name);
    File();
    ~File();

    const std::string &fileName() const { return name_; }
    void setFileName(const std::string &name);
    bool exists() const;

    bool open(OpenMode mode);
    bool isOpen() const { return fd_.isValid(); }
    OpenMode openMode() const { return mode_; }
    void close();

    int error() const { return error_; }
    ssize_t size() const;

    off_t pos() const;
    off_t seek(off_t pos);

    ssize_t read(const Span<uint8_t> &data);
    ssize_t write(const Span<const uint8_t> &data);

    Span<uint8_t> map(off_t offset = 0, ssize_t size = -1,
                      MapFlags flags = MapFlag::NoOption);
    bool unmap(uint8_t *addr);

    static bool exists(const std::string &name);

private:
    ZEUS_DISABLE_COPY(File)

    void unmapAll();

    std::string name_;
    UniqueFD fd_;
    OpenMode mode_;

    int error_;
    std::map<void *, size_t> maps_;
};

ZEUS_FLAGS_ENABLE_OPERATORS(File::MapFlag)
ZEUS_FLAGS_ENABLE_OPERATORS(File::OpenModeFlag)

} /* namespace zeus */
