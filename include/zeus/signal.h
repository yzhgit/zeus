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
// File: signal.h - Signal & slot implementation
//

#pragma once

#include <functional>
#include <list>
#include <type_traits>
#include <vector>

#include <zeus/bound_method.h>
#include <zeus/object.h>

namespace zeus {

class SignalBase
{
public:
    void disconnect(Object *object);

protected:
    using SlotList = std::list<BoundMethodBase *>;

    void connect(BoundMethodBase *slot);
    void disconnect(std::function<bool(SlotList::iterator &)> match);

    SlotList slots();

private:
    SlotList slots_;
};

template<typename... Args>
class Signal : public SignalBase
{
public:
    ~Signal()
    {
        disconnect();
    }

#ifndef __DOXYGEN__
    template<typename T, typename R, std::enable_if_t<std::is_base_of<Object, T>::value> * = nullptr>
    void connect(T *obj, R (T::*func)(Args...),
                 ConnectionType type = ConnectionTypeAuto)
    {
        Object *object = static_cast<Object *>(obj);
        SignalBase::connect(new BoundMethodMember<T, R, Args...>(obj, object, func, type));
    }

    template<typename T, typename R, std::enable_if_t<!std::is_base_of<Object, T>::value> * = nullptr>
#else
    template<typename T, typename R>
#endif
    void connect(T *obj, R (T::*func)(Args...))
    {
        SignalBase::connect(new BoundMethodMember<T, R, Args...>(obj, nullptr, func));
    }

#ifndef __DOXYGEN__
    template<typename T, typename Func,
             std::enable_if_t<std::is_base_of<Object, T>::value
#if __cplusplus >= 201703L
                              && std::is_invocable_v<Func, Args...>
#endif
                              > * = nullptr>
    void connect(T *obj, Func func, ConnectionType type = ConnectionTypeAuto)
    {
        Object *object = static_cast<Object *>(obj);
        SignalBase::connect(new BoundMethodFunctor<T, void, Func, Args...>(obj, object, func, type));
    }

    template<typename T, typename Func,
             std::enable_if_t<!std::is_base_of<Object, T>::value
#if __cplusplus >= 201703L
                              && std::is_invocable_v<Func, Args...>
#endif
                              > * = nullptr>
#else
    template<typename T, typename Func>
#endif
    void connect(T *obj, Func func)
    {
        SignalBase::connect(new BoundMethodFunctor<T, void, Func, Args...>(obj, nullptr, func));
    }

    template<typename R>
    void connect(R (*func)(Args...))
    {
        SignalBase::connect(new BoundMethodStatic<R, Args...>(func));
    }

    void disconnect()
    {
        SignalBase::disconnect([]([[maybe_unused]] SlotList::iterator &iter) {
            return true;
        });
    }

    template<typename T>
    void disconnect(T *obj)
    {
        SignalBase::disconnect([obj](SlotList::iterator &iter) {
            return (*iter)->match(obj);
        });
    }

    template<typename T, typename R>
    void disconnect(T *obj, R (T::*func)(Args...))
    {
        SignalBase::disconnect([obj, func](SlotList::iterator &iter) {
            BoundMethodArgs<R, Args...> *slot =
                    static_cast<BoundMethodArgs<R, Args...> *>(*iter);

            if (!slot->match(obj))
                return false;

            /*
			 * If the object matches the slot, the slot is
			 * guaranteed to be a member slot, so we can safely
			 * cast it to BoundMethodMember<T, Args...> to match
			 * func.
			 */
            return static_cast<BoundMethodMember<T, R, Args...> *>(slot)->match(func);
        });
    }

    template<typename R>
    void disconnect(R (*func)(Args...))
    {
        SignalBase::disconnect([func](SlotList::iterator &iter) {
            BoundMethodArgs<R, Args...> *slot =
                    static_cast<BoundMethodArgs<R, Args...> *>(*iter);

            if (!slot->match(nullptr))
                return false;

            return static_cast<BoundMethodStatic<R, Args...> *>(slot)->match(func);
        });
    }

    void emit(Args... args)
    {
        /*
		 * Make a copy of the slots list as the slot could call the
		 * disconnect operation, invalidating the iterator.
		 */
        for (BoundMethodBase *slot : slots())
            static_cast<BoundMethodArgs<void, Args...> *>(slot)->activate(args...);
    }
};

} /* namespace zeus */
