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
// File: thread_annotation.h - Macro of Clang thread safety analysis
//

#pragma once

/*
 * Enable thread safety attributes only with clang.
 * The attributes can be safely erased when compiling with other compilers.
 */
#if defined(__clang__) && !defined(SWIG)
#define ZEUS_TSA_ATTRIBUTE__(x) __attribute__((x))
#else
#define ZEUS_TSA_ATTRIBUTE__(x) /* no-op */
#endif

/* See https://clang.llvm.org/docs/ThreadSafetyAnalysis.html for these usages. */

#define ZEUS_TSA_CAPABILITY(x) \
    ZEUS_TSA_ATTRIBUTE__(capability(x))

#define ZEUS_TSA_SCOPED_CAPABILITY \
    ZEUS_TSA_ATTRIBUTE__(scoped_lockable)

#define ZEUS_TSA_GUARDED_BY(x) \
    ZEUS_TSA_ATTRIBUTE__(guarded_by(x))

#define ZEUS_TSA_PT_GUARDED_BY(x) \
    ZEUS_TSA_ATTRIBUTE__(pt_guarded_by(x))

#define ZEUS_TSA_ACQUIRED_BEFORE(...) \
    ZEUS_TSA_ATTRIBUTE__(acquired_before(__VA_ARGS__))

#define ZEUS_TSA_ACQUIRED_AFTER(...) \
    ZEUS_TSA_ATTRIBUTE__(acquired_after(__VA_ARGS__))

#define ZEUS_TSA_REQUIRES(...) \
    ZEUS_TSA_ATTRIBUTE__(requires_capability(__VA_ARGS__))

#define ZEUS_TSA_REQUIRES_SHARED(...) \
    ZEUS_TSA_ATTRIBUTE__(requires_shared_capability(__VA_ARGS__))

#define ZEUS_TSA_ACQUIRE(...) \
    ZEUS_TSA_ATTRIBUTE__(acquire_capability(__VA_ARGS__))

#define ZEUS_TSA_ACQUIRE_SHARED(...) \
    ZEUS_TSA_ATTRIBUTE__(acquire_shared_capability(__VA_ARGS__))

#define ZEUS_TSA_RELEASE(...) \
    ZEUS_TSA_ATTRIBUTE__(release_capability(__VA_ARGS__))

#define ZEUS_TSA_RELEASE_SHARED(...) \
    ZEUS_TSA_ATTRIBUTE__(release_shared_capability(__VA_ARGS__))

#define ZEUS_TSA_RELEASE_GENERIC(...) \
    ZEUS_TSA_ATTRIBUTE__(release_generic_capability(__VA_ARGS__))

#define ZEUS_TSA_TRY_ACQUIRE(...) \
    ZEUS_TSA_ATTRIBUTE__(try_acquire_capability(__VA_ARGS__))

#define ZEUS_TSA_TRY_ACQUIRE_SHARED(...) \
    ZEUS_TSA_ATTRIBUTE__(try_acquire_shared_capability(__VA_ARGS__))

#define ZEUS_TSA_EXCLUDES(...) \
    ZEUS_TSA_ATTRIBUTE__(locks_excluded(__VA_ARGS__))

#define ZEUS_TSA_ASSERT_CAPABILITY(x) \
    ZEUS_TSA_ATTRIBUTE__(assert_capability(x))

#define ZEUS_TSA_ASSERT_SHARED_CAPABILITY(x) \
    ZEUS_TSA_ATTRIBUTE__(assert_shared_capability(x))

#define ZEUS_TSA_RETURN_CAPABILITY(x) \
    ZEUS_TSA_ATTRIBUTE__(lock_returned(x))

#define ZEUS_TSA_NO_THREAD_SAFETY_ANALYSIS \
    ZEUS_TSA_ATTRIBUTE__(no_thread_safety_analysis)
