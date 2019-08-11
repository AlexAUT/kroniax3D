#pragma once

#include <aw/util/time/time.hpp>

namespace aw
{
class StopWatch
{
public:
  float restart();

  float getElapsedTime() const;

private:
  GameClock::time_point mStartPoint{GameClock::now()};
};
} // namespace aw
