#pragma once

#include <aw/util/log/log.hpp>
#include <aw/util/log/module.hpp>

namespace aw::log
{
inline Module engineLogModule("Engine");
}

#define LOG_ENGINE_F(...)                                                                          \
  aw::log::getDefaultLogger()->log(aw::log::engineLogModule, __FILE__, __LINE__, __func__,         \
                                   aw::log::Level::Fatal, __VA_ARGS__);
#define LOG_ENGINE_E(...)                                                                          \
  aw::log::getDefaultLogger()->log(aw::log::engineLogModule, __FILE__, __LINE__, __func__,         \
                                   aw::log::Level::Error, __VA_ARGS__);
#define LOG_ENGINE_W(...)                                                                          \
  aw::log::getDefaultLogger()->log(aw::log::engineLogModule, __FILE__, __LINE__, __func__,         \
                                   aw::log::Level::Warning, __VA_ARGS__);
#define LOG_ENGINE_D(...)                                                                          \
  aw::log::getDefaultLogger()->log(aw::log::engineLogModule, __FILE__, __LINE__, __func__,         \
                                   aw::log::Level::Debug, __VA_ARGS__);
#define LOG_ENGINE_V(...)                                                                          \
  aw::log::getDefaultLogger()->log(aw::log::engineLogModule, __FILE__, __LINE__, __func__,         \
                                   aw::log::Level::Verbose, __VA_ARGS__);
