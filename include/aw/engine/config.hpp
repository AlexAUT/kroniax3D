#pragma once

#include <aw/util/reflection/typeDescriptorClass.hpp>
#include <aw/util/reflection/types/primitiveTypes.hpp>
#include <aw/util/reflection/types/string.hpp>
#include <aw/util/serialization/nameValuePair.hpp>

#include <string>

namespace aw::engine
{
struct Config
{
  int test;
  struct AppConfig
  {
    std::string name;

    REFLECT();
  } application;

  struct WindowConfig
  {
    unsigned width;
    unsigned height;
    bool vsync;
    unsigned frameLimit;

    bool grabCursor;
    bool cursorVisible;

    unsigned depthBits;
    unsigned stencilBits;

    unsigned antialiasing;

    REFLECT();
  } window;

  REFLECT();
};
} // namespace aw::engine

// Reflect ApplicationConfig
REFLECT_BEGIN(aw::engine::Config::AppConfig)
REFLECT_MEMBER(name)
REFLECT_END(aw::engine::Config::AppConfig)

// Reflect WindowConfig
REFLECT_BEGIN(aw::engine::Config::WindowConfig)

REFLECT_MEMBER(width)
REFLECT_MEMBER(height)
REFLECT_MEMBER(vsync)
REFLECT_MEMBER(frameLimit)

REFLECT_MEMBER(grabCursor)
REFLECT_MEMBER(cursorVisible)

REFLECT_MEMBER(depthBits)
REFLECT_MEMBER(stencilBits)

REFLECT_MEMBER(antialiasing)

REFLECT_END(aw::engine::Config::WindowConfig)

// Reflect Config
REFLECT_BEGIN(aw::engine::Config)
REFLECT_MEMBER(test)
REFLECT_MEMBER(application)
REFLECT_MEMBER(window)
REFLECT_END(aw::engine::Config)
