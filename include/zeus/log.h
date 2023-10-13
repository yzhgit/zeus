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
// File: log.h - Logging infrastructure
//

#pragma once

#include <chrono>
#include <sstream>

#include <zeus/macros.h>
#include <zeus/private.h>
#include <zeus/utils.h>

namespace zeus {

enum LogSeverity {
    LogInvalid = -1,
    LogDebug = 0,
    LogInfo,
    LogWarning,
    LogError,
    LogFatal,
};

class LogCategory
{
public:
    static LogCategory *create(const char *name);

    const std::string &name() const { return name_; }
    LogSeverity severity() const { return severity_; }
    void setSeverity(LogSeverity severity);

    static const LogCategory &defaultCategory();

private:
    explicit LogCategory(const char *name);

    const std::string name_;
    LogSeverity severity_;
};

#define LOG_DECLARE_CATEGORY(name) \
    extern const LogCategory &_LOG_CATEGORY(name)();

#define LOG_DEFINE_CATEGORY(name)                                    \
    const LogCategory &_LOG_CATEGORY(name)()                         \
    {                                                                \
        /* The instance will be deleted by the Logger destructor. */ \
        static LogCategory *category = LogCategory::create(#name);   \
        return *category;                                            \
    }

class LogMessage
{
public:
    LogMessage(const char *fileName, unsigned int line,
               const LogCategory &category, LogSeverity severity,
               const std::string &prefix = std::string());

    LogMessage(LogMessage &&);
    ~LogMessage();

    std::ostream &stream() { return msgStream_; }

    const utils::time_point &timestamp() const { return timestamp_; }
    LogSeverity severity() const { return severity_; }
    const LogCategory &category() const { return category_; }
    const std::string &fileInfo() const { return fileInfo_; }
    const std::string &prefix() const { return prefix_; }
    const std::string msg() const { return msgStream_.str(); }

private:
    ZEUS_DISABLE_COPY(LogMessage)

    void init(const char *fileName, unsigned int line);

    std::ostringstream msgStream_;
    const LogCategory &category_;
    LogSeverity severity_;
    utils::time_point timestamp_;
    std::string fileInfo_;
    std::string prefix_;
};

class Loggable
{
public:
    virtual ~Loggable();

protected:
    virtual std::string logPrefix() const = 0;

    LogMessage _log(const LogCategory *category, LogSeverity severity,
                    const char *fileName = __builtin_FILE(),
                    unsigned int line = __builtin_LINE()) const;
};

LogMessage _log(const LogCategory *category, LogSeverity severity,
                const char *fileName = __builtin_FILE(),
                unsigned int line = __builtin_LINE());

#ifndef __DOXYGEN__
#define _LOG_CATEGORY(name) logCategory##name

#define _LOG1(severity) \
    _log(nullptr, Log##severity).stream()
#define _LOG2(category, severity) \
    _log(&_LOG_CATEGORY(category)(), Log##severity).stream()

/*
 * Expand the LOG() macro to _LOG1() or _LOG2() based on the number of
 * arguments.
 */
#define _LOG_MACRO(_1, _2, NAME, ...) NAME
#define LOG(...) _LOG_MACRO(__VA_ARGS__, _LOG2, _LOG1)(__VA_ARGS__)
#else /* __DOXYGEN___ */
#define LOG(category, severity)
#endif /* __DOXYGEN__ */

#ifndef NDEBUG
#define ASSERT(condition) static_cast<void>(({                  \
    if (!(condition))                                           \
        LOG(Fatal) << "assertion \"" #condition "\" failed in " \
                   << __func__ << "()";                         \
}))
#else
#define ASSERT(condition) static_cast<void>(false && (condition))
#endif

} /* namespace zeus */
