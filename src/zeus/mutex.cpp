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
// File: mutex.cpp - Mutex classes with clang thread safety annotation
//

#include <zeus/mutex.h>

/**
 * \file base/mutex.h
 * \brief Mutex classes with clang thread safety annotation
 */

namespace zeus {

/**
 * \class Mutex
 * \brief std::mutex wrapper with clang thread safety annotation
 *
 * The Mutex class wraps a std::mutex instance to add clang thread safety
 * annotation support. The class exposes the same interface as std::mutex and
 * can be used as a transparent replacement. It integrates with the
 * MutexLocker and ConditionVariable classes.
 *
 * See https://en.cppreference.com/w/cpp/thread/mutex for the complete API
 * documentation.
 */

/**
 * \class MutexLocker
 * \brief std::unique_lock wrapper with clang thread safety annotation
 *
 * The MutexLocker class wraps a std::unique_lock instance to add clang thread
 * safety annotation support. The class exposes the same interface as
 * std::unique_lock and can be used as a transparent replacement. It integrates
 * with the Mutex and ConditionVariable classes.
 *
 * See https://en.cppreference.com/w/cpp/thread/unique_lock for the complete API
 * documentation.
 */

/**
 * \class ConditionVariable
 * \brief std::condition_variable wrapper integrating with MutexLocker
 *
 * The ConditionVariable class wraps a std::condition_variable instance to
 * integrate with the MutexLocker class. The class exposes the same interface as
 * std::condition_variable and can be used as a transparent replacement.
 *
 * See https://en.cppreference.com/w/cpp/thread/condition_variable for the
 * complete API documentation.
 */

} /* namespace zeus */
