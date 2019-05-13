#pragma once

#include <chrono>

#include <aw/util/time/time.hpp>

namespace aw
{

class Clock
{
public:
  template <typename TimeUnit = Seconds>
  float restart();

  template <typename TimeUnit>
  float getElapsedTime() const;

private:
  TimePoint mStartPoint{std::chrono::high_resolution_clock::now()};
};

template <typename TimeUnit>
float Clock::restart()
{
  TimePoint oldStart = mStartPoint;
  mStartPoint = std::chrono::high_resolution_clock::now();
  return std::chrono::duration_cast<TimeUnit>(mStartPoint - oldStart).count();
}

template <typename TimeUnit>
float Clock::getElapsedTime() const
{
  TimePoint now = std::chrono::high_resolution_clock::now();
  return std::chrono::duration<TimeUnit>(now - mStartPoint).count();
}
} // namespace aw
