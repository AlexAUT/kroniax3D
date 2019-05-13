#pragma once

namespace aw::windowEvent
{
struct Closed
{
};

struct Resized
{
  unsigned width, height;
};

struct LostFocus
{
};

struct GainedFocus
{
};
} // namespace aw::windowEvent
