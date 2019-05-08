#pragma once

#include <aw/engine/config.hpp>
#include <aw/engine/window.hpp>
#include <aw/util/file/pathRegistry.hpp>
#include <aw/util/message/bus.hpp>

namespace aw::engine
{
class Engine
{
public:
  Engine();

  int run();

  void step();

  void terminate(bool exitCode = 0);

  msg::Bus& messageBus();
  const msg::Bus& messageBus() const;

private:
private:
  bool mRunning{true};
  int mExitCode;

  Config mConfig{Config::load()};
  msg::Bus mMessageBus;

  Window mMainWindow{mConfig, mMessageBus};
};
} // namespace aw::engine
