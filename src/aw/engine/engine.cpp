#include <aw/engine/engine.hpp>

#include <aw/config.hpp>
#include <aw/engine/logEngine.hpp>
#include <aw/opengl/opengl.hpp>
#include <aw/util/log/log.hpp>

#include <SFML/Window/Event.hpp>

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

namespace aw
{
Engine::Engine() : mWindow({800, 600}, "Engine test")
{
  mWindow.setVerticalSyncEnabled(true);
  assert(log::getDefaultLogger() && "You need to set the default logger before using the engine!");
}

int Engine::run()
{
#ifdef AW_OS_EMSCRIPTEN
  // void emscripten_set_main_loop(em_callback_func func, int fps, int simulate_infinite_loop);
  priv::instance = this;
  emscripten_set_main_loop(priv::step, 60, 1);
#else
  while (mWindow.isOpen())
  {
    step();
  }
#endif
  return 0;
} // namespace aw

void Engine::step()
{
  sf::Event event;
  while (mWindow.pollEvent(event))
  {
    if (event.type == sf::Event::MouseMoved)
    {
      LOG_ENGINE(log::Level::Debug, "Mouse moved?");
    }
    if (event.type == sf::Event::Closed)
      mWindow.close();
  }
  glClearColor(1.0f, 1.0f, 0.f, 1.f);
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
  mWindow.display();
}
} // namespace aw
