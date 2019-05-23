#include <aw/engine/window/window.hpp>

#include <aw/engine/log.hpp>
#include <aw/engine/window/event.hpp>

#include <SFML/Window/Event.hpp>
#include <SFML/Window/Mouse.hpp>

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
      mMessageBus.channel<windowEvent::Resized>().broadcast(
          {{event.size.width, event.size.height}});
      break;
    case sf::Event::GainedFocus:
      mMessageBus.channel<windowEvent::GainedFocus>().broadcast({});
      break;
    case sf::Event::LostFocus:
      mMessageBus.channel<windowEvent::LostFocus>().broadcast({});
      break;
    case sf::Event::MouseMoved:
    {
      math::Vec2i mousePos{event.mouseMove.x, event.mouseMove.y};
      auto delta = mousePos - mLastMousePos;
      mLastMousePos = mousePos;

      if (!mFirstMouseMoved)
        mMessageBus.channel<windowEvent::MouseMoved>().broadcast({mousePos, delta});
      else
        mFirstMouseMoved = false;

      break;
    }
    case sf::Event::MouseButtonPressed:
      mMessageBus.channel<windowEvent::MouseButtonPressed>().broadcast(
          {static_cast<mouse::Button>(event.mouseButton.button),
           {event.mouseButton.x, event.mouseButton.y}});
      break;
    case sf::Event::MouseButtonReleased:
      mMessageBus.channel<windowEvent::MouseButtonReleased>().broadcast(
          {static_cast<mouse::Button>(event.mouseButton.button),
           {event.mouseButton.x, event.mouseButton.y}});
      break;
    case sf::Event::MouseWheelScrolled:
      mMessageBus.channel<windowEvent::MouseWheelScrolled>().broadcast(
          {static_cast<mouse::Wheel>(event.mouseWheelScroll.wheel),
           {event.mouseWheelScroll.x, event.mouseWheelScroll.y},
           event.mouseWheelScroll.delta});
      break;
    case sf::Event::MouseWheelMoved:
      break; // Deprecated
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
