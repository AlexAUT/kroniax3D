#include <aw/engine/window.hpp>

#include <aw/engine/logEngine.hpp>
#include <aw/engine/windowEvent.hpp>

#include <SFML/Window/Event.hpp>

namespace aw::engine
{
Window::Window(const Config& config, const msg::Bus& bus) :
    mMessageBus(bus),
    mWindow({config.window.width, config.window.height}, config.application.name,
            sf::Style::Default,
            sf::ContextSettings{
                config.window.depthBits,
                config.window.stencilBits,
            })
{
  mWindow.setVerticalSyncEnabled(config.window.vsync);
  mWindow.setFramerateLimit(config.window.frameLimit);

  mWindow.setMouseCursorGrabbed(config.window.grabCursor);
  mWindow.setMouseCursorVisible(config.window.cursorVisible);
}

void Window::handleEvents()
{
  sf::Event event;
  while (mWindow.pollEvent(event))
  {
    switch (event.type)
    {
    case sf::Event::Closed:
      mMessageBus.channel<windowEvent::Closed>().broadcast(windowEvent::Closed{});
      break;
    default:
      LOG_ENGINE(log::Level::Warning, "Event translation not implemented {}\n", event.type);
    }
  }
}

void Window::display()
{
  mWindow.display();
}
} // namespace aw::engine
