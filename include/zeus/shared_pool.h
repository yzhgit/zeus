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
// File: bound_method.h - Method bind and invocation
//

#pragma once

#include <algorithm>
#include <cassert>
#include <cstdint>
#include <functional>
#include <list>
#include <memory>
#include <mutex>
#include <type_traits>
#include <utility>

#include <zeus/macros.h>

namespace zeus {

template<typename T>
class SharedPool
{
public:
    using ValuePtr = std::shared_ptr<T>;
    using AllocateFunction = std::function<ValuePtr()>;

    SharedPool()
            : m_pool(std::make_shared<impl>(
                      AllocateFunction(std::make_shared<T>)))
    {
    }

    ValuePtr allocate()
    {
        assert(m_pool);
        return m_pool->allocate();
    }

private:
    class impl : public std::enable_shared_from_this<impl>
    {
    public:
        impl(AllocateFunction allocate)
                : m_allocate(std::move(allocate))
        {
            assert(m_allocate);
        }

        impl(const impl &other)
                : std::enable_shared_from_this<impl>(other),
                  m_allocate(other.m_allocate)
        {
            std::size_t size = other.unused_resources();
            for (std::size_t i = 0; i < size; ++i) {
                m_free_list.push_back(m_allocate());
            }
        }

        impl(impl &&other)
                : std::enable_shared_from_this<impl>(other),
                  m_allocate(std::move(other.m_allocate)),
                  m_free_list(std::move(other.m_free_list))
        {
        }

        impl &operator=(const impl &other)
        {
            impl tmp(other);
            std::swap(*this, tmp);
            return *this;
        }

        impl &operator=(impl &&other)
        {
            m_allocate = std::move(other.m_allocate);
            m_free_list = std::move(other.m_free_list);
            return *this;
        }

        ValuePtr allocate()
        {
            ValuePtr resource;
            {
                std::lock_guard<std::mutex> lock(m_mutex);
                if (m_free_list.size() > 0) {
                    resource = m_free_list.back();
                    m_free_list.pop_back();
                }
            }

            if (!resource) {
                assert(m_allocate);
                resource = m_allocate();
            }

            auto pool = impl::shared_from_this();

            return ValuePtr(resource.get(), deleter(pool, resource));
        }

        void recycle(const ValuePtr &resource)
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            m_free_list.push_back(resource);
        }

        std::size_t unused_resources() const
        {
            std::lock_guard<std::mutex> lock(m_mutex);
            return m_free_list.size();
        }

    private:
        AllocateFunction m_allocate;
        std::list<ValuePtr> m_free_list;
        mutable std::mutex m_mutex;
    };

    class deleter
    {
    public:
        deleter(const std::weak_ptr<impl> &pool, const ValuePtr &resource)
                : m_pool(pool), m_resource(resource)
        {
            assert(!m_pool.expired());
            assert(m_resource);
        }

        void operator()(T *)
        {
            auto pool = m_pool.lock();

            if (pool) {
                pool->recycle(m_resource);
            }
            m_resource.reset();
        }

    private:
        std::weak_ptr<impl> m_pool;
        ValuePtr m_resource;
    };
    ZEUS_DISABLE_COPY_AND_MOVE(SharedPool)

    std::shared_ptr<impl> m_pool;
};

} // namespace zeus
