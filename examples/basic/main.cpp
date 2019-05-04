#include <iostream>
#include <thread>

#include <aw/engine/engine.hpp>
#include <aw/engine/logEngine.hpp>
#include <aw/util/log/consoleSink.hpp>
#include <aw/util/log/log.hpp>
#include <aw/util/log/logger.hpp>

int main()
{
  auto logger = std::make_shared<aw::log::Logger>();
  logger->addSink(std::make_shared<aw::log::ConsoleSink>());

  aw::log::setDefaultLogger(logger);

  aw::Engine engine;
  engine.run();

  LOG_ENGINE(aw::log::Level::Debug, "Close main!");
}
