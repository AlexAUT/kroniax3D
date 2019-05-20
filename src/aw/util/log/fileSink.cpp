#include <aw/util/log/fileSink.hpp>

#include <aw/util/log/message.hpp>

#include <fmt/ostream.h>

namespace aw::log
{
FileSink::FileSink(std::string_view path) :
    mFile{path.data(), std::ios::out | std::ios::trunc} {} // namespace aw::log

void FileSink::log(const Message& msg)
{
  if (mLogTimeSinceStart)
  {
    auto time = std::chrono::steady_clock::now();
    auto milliseconds =
        std::chrono::duration_cast<std::chrono::milliseconds>(time - mStartTimePoint);
    fmt::print(mFile, "{}[{:9.3f}]{}: {}\n", levelToString(msg.level),
               milliseconds.count() / 1000.f, msg.module, msg.message.data());
  }
  else
  {
    fmt::print(mFile, "{}{}: {}\n", levelToString(msg.level), msg.module, msg.message.data());
  }
}
} // namespace aw::log
