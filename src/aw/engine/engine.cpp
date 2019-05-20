#include <aw/engine/engine.hpp>

#include <aw/config.hpp>
#include <aw/engine/log.hpp>
#include <aw/opengl/opengl.hpp>
#include <aw/util/log/log.hpp>

#include <iostream>

#ifdef AW_OS_EMSCRIPTEN
namespace priv
{
aw::Engine* instance{nullptr};
void step()
{
  instance->step();
}
} // namespace priv
#endif

namespace aw ::engine
{
Engine::Engine()
{
  assert(log::getDefaultLogger() && "You need to set the default logger before using the engine!");
} // namespace aw::engineEngine::Engine():mWindow(

int Engine::run()
{
#ifdef AW_OS_EMSCRIPTEN
  // void emscripten_set_main_loop(em_callback_func func, int fps, int simulate_infinite_loop);
  priv::instance = this;
  emscripten_set_main_loop(priv::step, 60, 1);
#else
  while (mRunning)
  {
    step();
  }
#endif
  return 0;
}

void Engine::step()
{
  const auto dt = mFrameClock.restart();

  mMainWindow.handleEvents();

  mStateMachine.update(dt);
  mStateMachine.render();

  mMainWindow.display();
}

void Engine::terminate(bool exitCode)
{
  mExitCode = exitCode;
  mRunning = false;
}

msg::Bus& Engine::messageBus()
{
  return mMessageBus;
}

const msg::Bus& Engine::messageBus() const
{
  return mMessageBus;
}

StateMachine& Engine::stateMachine()
{
  return mStateMachine;
}
const StateMachine& Engine::stateMachine() const
{
  return mStateMachine;
}

} // namespace aw::engine
