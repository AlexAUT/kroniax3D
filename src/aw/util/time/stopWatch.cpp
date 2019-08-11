#include <aw/util/time/stopWatch.hpp>

namespace aw
{
using Seconds = std::chrono::duration<float>;

float StopWatch::restart()
{
  GameClock::time_point oldStart = mStartPoint;
  mStartPoint = GameClock::now();
  return std::chrono::duration_cast<Seconds>(mStartPoint - oldStart).count();
}

float StopWatch::getElapsedTime() const
{
  GameClock::time_point now = GameClock::now();
  return std::chrono::duration_cast<Seconds>(now - mStartPoint).count();
}
} // namespace aw
