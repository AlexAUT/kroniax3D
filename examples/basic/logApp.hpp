#pragma once

#include <aw/util/log/log.hpp>
#include <aw/util/log/module.hpp>

namespace aw::log
{
inline Module appLogModule("App");
}

#define LOG_APP_F(...)                                                                             \
  aw::log::getDefaultLogger()->log(aw::log::appLogModule, __FILE__, __LINE__, __func__,            \
                                   aw::log::Level::Fatal, __VA_ARGS__);
#define LOG_APP_E(...)                                                                             \
  aw::log::getDefaultLogger()->log(aw::log::appLogModule, __FILE__, __LINE__, __func__,            \
                                   aw::log::Level::Error, __VA_ARGS__);
#define LOG_APP_W(...)                                                                             \
  aw::log::getDefaultLogger()->log(aw::log::appLogModule, __FILE__, __LINE__, __func__,            \
                                   aw::log::Level::Warning, __VA_ARGS__);
#define LOG_APP_D(...)                                                                             \
  aw::log::getDefaultLogger()->log(aw::log::appLogModule, __FILE__, __LINE__, __func__,            \
                                   aw::log::Level::Debug, __VA_ARGS__);
#define LOG_APP_V(...)                                                                             \
  aw::log::getDefaultLogger()->log(aw::log::appLogModule, __FILE__, __LINE__, __func__,            \
                                   aw::log::Level::Verbose, __VA_ARGS__);
