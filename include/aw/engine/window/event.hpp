#pragma once

#include <aw/engine/window/mouse.hpp>
#include <aw/util/math/vector.hpp>

namespace aw::windowEvent
{
struct Closed
{
};

struct Resized
{
  math::Vec2u size;
};

struct LostFocus
{
};

struct GainedFocus
{
};

struct MouseMoved
{
  math::Vec2i pos;
  math::Vec2i delta;
};

struct MouseButtonPressed
{
  mouse::Button button;
  math::Vec2i pos;
};

struct MouseButtonReleased
{
  mouse::Button button;
  math::Vec2i pos;
};
} // namespace aw::windowEvent
