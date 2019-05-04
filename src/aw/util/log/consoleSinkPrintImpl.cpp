#include <aw/util/log/consoleSink.hpp>

#include <aw/util/log/message.hpp>

#include <fmt/core.h>

namespace aw::log
{
std::string_view levelToColor(Level level)
{
  switch (level)
  {
  case Level::Fatal:
    return "\033[1;31m";
  case Level::Error:
    return "\033[0;31m";
  case Level::Warning:
    return "\033[1;33m";
  case Level::Debug:
    return "\033[1;34m";
  case Level::Verbose:
    return "";
  default:
    assert("Unsupported log level!");
    return "";
  }
}

void ConsoleSink::logTimeSinceStart(bool value)
{
  mLogTimeSinceStart = value;
}

void ConsoleSink::log(const Message& msg)
{
  if (mColored)
    fmt::print("{}", levelToColor(msg.level));
  else
    fmt::print("{} ", levelToString(msg.level));

  auto printHeader = mLogTimeSinceStart || mLogFileName || mLogLineNumber || mLogFunctionName;

  if (printHeader)
    fmt::print("[");

  if (mLogTimeSinceStart)
  {
    using namespace std::chrono;
    auto time = duration_cast<milliseconds>(steady_clock::now() - mStartTimePoint).count() / 1000.f;
    fmt::print("{:7.3f}", time);
  }

  if (mLogFileName)
  {
    if (mLogTimeSinceStart)
      fmt::print(" ");

    if (mTruncateFileName)
    {
      std::string_view v(msg.fileName);
      auto cutPos = v.find_last_of("/");
      if (cutPos != std::string_view::npos)
        v = v.substr(cutPos + 1);
      fmt::print("{}", v);
    }
    else
      fmt::print("{}", msg.fileName);
  }
  if (mLogFunctionName)
  {
    if (mLogFileName)
      fmt::print(":");
    fmt::print("{}", msg.functionName);
  }
  if (mLogLineNumber)
    fmt::print(":{}", msg.lineNumber);

  if (printHeader)
    fmt::print("]");

  fmt::print("{}: ", msg.module);

  if (mColored)
    fmt::print("\033[0m");

  fmt::print("{}\n", msg.message.data());
}
} // namespace aw::log
