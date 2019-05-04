#pragma once

#include <aw/util/containers/ringBuffer.hpp>
#include <aw/util/log/level.hpp>
#include <aw/util/log/message.hpp>
#include <aw/util/log/module.hpp>
#include <aw/util/log/sink.hpp>

#define FMT_STRING_ALIAS 1
#include <fmt/format.h>

#include <chrono>
#include <cstdint>
#include <thread>
#include <vector>

namespace aw::log
{
class Logger
{
public:
  Logger() = default;
  Logger(unsigned queueSize);
  Logger(unsigned queueSize, std::chrono::microseconds flushInterval);
  ~Logger();
  Logger(const Logger&) = delete;
  Logger& operator=(const Logger&) = delete;

  void enableLevel(Level level);
  void disableLevel(Level level);
  bool isLevelEnabled(Level level) const;

  // This function is only save if there are no messages in the pipeline for the whole duration
  void addSink(std::shared_ptr<log::Sink> sink);

  template <typename... Args>
  void log(const Module& module, const char* fileName, int lineNumber, const char* functionName, Level level,
           const char* formatString, Args&&... args);

private:
  void sinkThread();

private:
  bool mRunning{true};
  unsigned char mLevelEnabled{0xFF};

  // Message Queue
  unsigned mBufferCount{50};
  RingBufferController mBufferController{mBufferCount};

  std::vector<Message> mMessageBuffer{mBufferCount};

  std::vector<std::shared_ptr<log::Sink>> mSinks;

  std::chrono::microseconds mFlushInterval{10'000};
  std::thread mSinkThread{[this]() { sinkThread(); }};
};
} // namespace aw::log

// Implementation

namespace aw::log
{
// Define it here to get inlining
inline bool Logger::isLevelEnabled(Level level) const
{
  return (mLevelEnabled >> static_cast<LevelUnderlyingType>(level)) & 1U;
}

template <typename... Args>
void Logger::log(const Module& module, const char* fileName, int lineNumber, const char* functionName, Level level,
                 const char* formatString, Args&&... args)
{
  if (!isLevelEnabled(level) || !module.isLevelEnabled(level))
    return;

  if (mBufferController.full())
  {
    fmt::print("Losing messages because ring buffer is full!\n");
    return;
  }
  auto loc = mBufferController.writer();

  mMessageBuffer[loc].module = module.name();
  mMessageBuffer[loc].fileName = fileName;
  mMessageBuffer[loc].lineNumber = lineNumber;
  mMessageBuffer[loc].functionName = functionName;
  mMessageBuffer[loc].level = level;
  fmt::format_to(mMessageBuffer[loc].message, formatString, std::forward<Args...>(args)...);

  std::atomic_thread_fence(std::memory_order_seq_cst);
  mBufferController.increateWriter();
}
} // namespace aw::log
