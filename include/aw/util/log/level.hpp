#pragma once

#include <cassert>
#include <cstdint>

namespace aw::log
{
using LevelUnderlyingType = std::int8_t;
enum class Level : LevelUnderlyingType
{
  Fatal,
  Error,
  Warning,
  Debug,
  Verbose
};

inline const char* levelToString(Level level)
{
  switch (level)
  {
  case Level::Fatal:
    return "F";
  case Level::Error:
    return "E";
  case Level::Warning:
    return "W";
  case Level::Debug:
    return "D";
  case Level::Verbose:
    return "V";
  default:
    assert("Invalid log level?");
    return "";
  }
}
} // namespace aw::log
