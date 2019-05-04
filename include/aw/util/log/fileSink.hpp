#pragma once

#include <aw/util/log/level.hpp>
#include <aw/util/log/sink.hpp>
#include <chrono>
#include <fstream>

namespace aw::log
{
struct Message;

class FileSink : public Sink
{
public:
  FileSink(std::string_view path);

  void logTimeSinceStart(bool value);
  virtual void log(const Message& msg) final override;

public:
  bool mLogTimeSinceStart{true};
  std::fstream mFile;
  std::chrono::steady_clock::time_point mStartTimePoint{std::chrono::steady_clock::now()};
};
} // namespace aw::log
