#pragma once

#include <aw/util/log/level.hpp>

namespace aw::log
{
class Module
{
public:
  Module(const char* name);

  void enableLevel(Level level);
  void disableLevel(Level level);
  bool isLevelEnabled(Level level) const;

  const char* name() const;

private:
  const char* mName;

  unsigned char mLevelEnabled{0xFF};
};
} // namespace aw::log

namespace aw::log
{
inline const char* Module::name() const
{
  return mName;
}

// Define it here to get inlining
inline bool Module::isLevelEnabled(Level level) const
{
  return (mLevelEnabled >> static_cast<LevelUnderlyingType>(level)) & 1U;
}
} // namespace aw::log
