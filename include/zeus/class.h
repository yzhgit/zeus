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
// File: class.h - Utilities and helpers for classes
//

#pragma once

#include <memory>

namespace zeus {

#ifndef __DOXYGEN__
#define ZEUS_DECLARE_PRIVATE()            \
public:                                   \
    class Private;                        \
    friend class Private;                 \
    template<bool B = true>               \
    const Private *_d() const             \
    {                                     \
        return Extensible::_d<Private>(); \
    }                                     \
    template<bool B = true>               \
    Private *_d()                         \
    {                                     \
        return Extensible::_d<Private>(); \
    }

#define ZEUS_DECLARE_PUBLIC(klass) \
    friend class klass;            \
    using Public = klass;

#define ZEUS_O_PTR() \
    _o<Public>()

#else
#define ZEUS_DECLARE_PRIVATE()
#define ZEUS_DECLARE_PUBLIC(klass)
#define ZEUS_O_PTR()
#endif

class Extensible
{
public:
    class Private
    {
    public:
        Private();
        virtual ~Private();

#ifndef __DOXYGEN__
        template<typename T>
        const T *_o() const
        {
            return static_cast<const T *>(o_);
        }

        template<typename T>
        T *_o()
        {
            return static_cast<T *>(o_);
        }
#endif

    private:
        /* To initialize o_ from Extensible. */
        friend class Extensible;
        Extensible *const o_;
    };

    Extensible(std::unique_ptr<Private> d);

protected:
    template<typename T>
    const T *_d() const
    {
        return static_cast<const T *>(d_.get());
    }

    template<typename T>
    T *_d()
    {
        return static_cast<T *>(d_.get());
    }

private:
    const std::unique_ptr<Private> d_;
};

} /* namespace zeus */
