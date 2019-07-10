#pragma once

#include <aw/engine/window/keyboard.hpp>
#include <aw/engine/window/mouse.hpp>
#include <aw/util/math/vector.hpp>

namespace aw::windowEvent
{
struct Closed
{
};

struct Resized
{
  Vec2u size;
};

struct LostFocus
{
};

struct GainedFocus
{
};

struct MouseMoved
{
  Vec2i pos;
  Vec2i delta;
};

struct MouseButtonPressed
{
  mouse::Button button;
  Vec2i pos;
};

struct MouseButtonReleased
{
  mouse::Button button;
  Vec2i pos;
};

struct MouseWheelScrolled
{
  mouse::Wheel wheel;
  Vec2i pos;
  float delta;
};

struct KeyPressed
{
  keyboard::Key key;
};

struct KeyReleased
{
  keyboard::Key key;
};
} // namespace aw::windowEvent
