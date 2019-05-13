#pragma once

#include <chrono>

namespace aw
{
using TimePoint = std::chrono::time_point<std::chrono::high_resolution_clock>;
using Seconds = std::chrono::duration<float>;
using MilliSeconds = std::chrono::duration<float, std::milli>;
using MicroSeconds = std::chrono::duration<float, std::micro>;
using NanoSeconds = std::chrono::duration<float, std::nano>;
} // namespace aw
