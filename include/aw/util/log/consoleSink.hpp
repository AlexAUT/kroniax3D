#pragma once

#include <aw/util/log/level.hpp>
#include <aw/util/log/sink.hpp>
#include <chrono>

namespace aw::log
{
struct Message;

class ConsoleSink : public Sink
{
public:
  void colored(bool value);
  void logTimeSinceStart(bool value);
  void truncateFileName(bool value);
  void logLineNumber(bool value);
  void logFunctionName(bool value);
  void logFileName(bool value);
  virtual void log(const Message& msg) final override;

public:
  bool mColored{true};
  bool mLogTimeSinceStart{true};

  bool mLogFileName{true};
  bool mTruncateFileName{true};
  bool mLogFunctionName{true};
  bool mLogLineNumber{true};

  std::chrono::steady_clock::time_point mStartTimePoint{std::chrono::steady_clock::now()};
};
} // namespace aw::log
