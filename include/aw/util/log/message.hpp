#pragma once

#include <aw/util/log/level.hpp>
#include <string>

#include <fmt/format.h>

namespace aw::log
{
struct Message
{
  const char* module;
  const char* fileName;
  int lineNumber;
  const char* functionName;
  Level level;
  fmt::memory_buffer message;
};
} // namespace aw::log
