#pragma once

#include <aw/util/log/log.hpp>
#include <aw/util/log/module.hpp>

namespace aw::log
{
inline Module graphicsLogModule("Graphics");
}

#define LOG_GRAPHICS_F(...)                                                                        \
  aw::log::getDefaultLogger()->log(aw::log::graphicsLogModule, __FILE__, __LINE__, __func__,       \
                                   aw::log::Level::Fatal, __VA_ARGS__);
#define LOG_GRAPHICS_E(...)                                                                        \
  aw::log::getDefaultLogger()->log(aw::log::graphicsLogModule, __FILE__, __LINE__, __func__,       \
                                   aw::log::Level::Error, __VA_ARGS__);
#define LOG_GRAPHICS_W(...)                                                                        \
  aw::log::getDefaultLogger()->log(aw::log::graphicsLogModule, __FILE__, __LINE__, __func__,       \
                                   aw::log::Level::Warning, __VA_ARGS__);
#define LOG_GRAPHICS_D(...)                                                                        \
  aw::log::getDefaultLogger()->log(aw::log::graphicsLogModule, __FILE__, __LINE__, __func__,       \
                                   aw::log::Level::Debug, __VA_ARGS__);
#define LOG_GRAPHICS_V(...)                                                                        \
  aw::log::getDefaultLogger()->log(aw::log::graphicsLogModule, __FILE__, __LINE__, __func__,       \
                                   aw::log::Level::Verbose, __VA_ARGS__);
