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
// File: backtrace.h - Call stack backtraces
//

#pragma once

#include <string>
#include <vector>

#include <zeus/macros.h>
#include <zeus/private.h>

namespace zeus {

class Backtrace
{
public:
    Backtrace();

    std::string toString(unsigned int skipLevels = 0) const;

private:
    ZEUS_DISABLE_COPY(Backtrace)

    bool backtraceTrace();
    bool unwindTrace();

    std::vector<void *> backtrace_;
    std::vector<std::string> backtraceText_;
};

} /* namespace zeus */
