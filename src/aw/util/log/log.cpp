#include <aw/util/log/log.hpp>

namespace aw::log
{
std::shared_ptr<Logger> defaultLogger{nullptr};

Logger* getDefaultLogger()
{
  return defaultLogger.get();
}

void setDefaultLogger(std::shared_ptr<Logger> logger)
{
  defaultLogger = std::move(logger);
}
} // namespace aw::log
