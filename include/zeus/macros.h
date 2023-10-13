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
// File: macros.h - macro helpers
//

#pragma once

namespace zeus {

#ifndef __DOXYGEN__
#define ZEUS_DISABLE_COPY(klass)   \
    klass(const klass &) = delete; \
    klass &operator=(const klass &) = delete;

#define ZEUS_DISABLE_MOVE(klass) \
    klass(klass &&) = delete;    \
    klass &operator=(klass &&) = delete;

#define ZEUS_DISABLE_COPY_AND_MOVE(klass) \
    ZEUS_DISABLE_COPY(klass)              \
    ZEUS_DISABLE_MOVE(klass)
#else
#define ZEUS_DISABLE_COPY(klass)
#define ZEUS_DISABLE_MOVE(klass)
#define ZEUS_DISABLE_COPY_AND_MOVE(klass)
#endif

} // namespace zeus
