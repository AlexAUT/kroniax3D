#include <iostream>
#include <thread>

#include <aw/engine/engine.hpp>
#include <aw/engine/logEngine.hpp>
#include <aw/engine/window/event.hpp>
#include <aw/util/log/consoleSink.hpp>
#include <aw/util/log/log.hpp>
#include <aw/util/log/logger.hpp>

#include <aw/util/file/pathRegistry.hpp>

#include "basicState.hpp"

#include <fstream>

int main()
{
  auto logger = std::make_shared<aw::log::Logger>();
  logger->addSink(std::make_shared<aw::log::ConsoleSink>());

  aw::log::setDefaultLogger(logger);

  aw::engine::Engine engine;

  auto initialState = std::make_shared<BasicState>(engine);
  engine.stateMachine().pushState(initialState);

  int returnValue = engine.run();

  LOG_ENGINE(aw::log::Level::Debug, "Closing application!");

  return returnValue;
}
