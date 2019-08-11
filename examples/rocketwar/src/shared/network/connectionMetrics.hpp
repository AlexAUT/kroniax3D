#pragma once

#include <aw/util/time/time.hpp>

namespace network
{
struct ConnectionMetrics
{
  float rtt{0.2f};
  float rttVariance{0.f};
  float packageLoss{0.f};
};
} // namespace network
