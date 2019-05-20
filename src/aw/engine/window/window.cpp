#include <aw/engine/window/window.hpp>

#include <aw/engine/log.hpp>
#include <aw/engine/window/event.hpp>

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
      mMessageBus.channel<windowEvent::Closed>().broadcast({});
      break;
    case sf::Event::Resized:
      mMessageBus.channel<windowEvent::Resized>().broadcast({event.size.width, event.size.height});
      break;
    case sf::Event::GainedFocus:
      mMessageBus.channel<windowEvent::GainedFocus>().broadcast({});
      break;
    case sf::Event::LostFocus:
      mMessageBus.channel<windowEvent::LostFocus>().broadcast({});
    default:
      LOG_ENGINE_W("Event translation not implemented {}\n", event.type);
    }
  }
}

void Window::display()
{
  mWindow.display();
}
} // namespace aw::engine
