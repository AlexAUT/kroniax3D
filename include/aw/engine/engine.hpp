#pragma once

#include <aw/engine/config.hpp>
#include <aw/engine/stateMachine/stateMachine.hpp>
#include <aw/engine/window/window.hpp>
#include <aw/util/file/pathRegistry.hpp>
#include <aw/util/message/bus.hpp>
#include <aw/util/time/clock.hpp>

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

  StateMachine& stateMachine();
  const StateMachine& stateMachine() const;

private:
private:
  bool mRunning{true};
  int mExitCode;

  Config mConfig{Config::load()};
  msg::Bus mMessageBus;

  Window mMainWindow{mConfig, mMessageBus};
  StateMachine mStateMachine;

  Clock mFrameClock;
};
} // namespace aw::engine
