#pragma once

#include <aw/util/reflection/typeDescriptorClass.hpp>
#include <aw/util/reflection/types/primitiveTypes.hpp>
#include <aw/util/reflection/types/string.hpp>

#include <string>

namespace aw
{
class PathRegistry;
}

namespace aw::engine
{
struct Config
{
  static Config load();
  static void save();

  struct AppConfig
  {
    std::string name{"awEngine"};

    REFLECT();
  } application;

  struct WindowConfig
  {
    unsigned width{800};
    unsigned height{600};
    bool vsync{true};
    unsigned frameLimit{0};

    bool grabCursor{false};
    bool cursorVisible{true};

    unsigned depthBits{8};
    unsigned stencilBits{0};

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

REFLECT_END(aw::engine::Config::WindowConfig)

// Reflect Config
REFLECT_BEGIN(aw::engine::Config)
REFLECT_MEMBER(application)
REFLECT_MEMBER(window)
REFLECT_END(aw::engine::Config)
