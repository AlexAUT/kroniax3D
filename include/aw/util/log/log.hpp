#pragma once

#include <aw/util/log/logger.hpp>

#include <memory>

namespace aw::log
{
Logger* getDefaultLogger();
void setDefaultLogger(std::shared_ptr<Logger> logger);
} // namespace aw::log

