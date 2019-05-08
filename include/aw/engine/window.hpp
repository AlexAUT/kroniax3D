#pragma once

#include <aw/engine/config.hpp>
#include <aw/util/message/bus.hpp>

#include <SFML/Window/Window.hpp>

namespace aw::engine
{
class Window
{
public:
  Window(const Config& config, const msg::Bus& bus);

  void handleEvents();

  void display();

public:
private:
  const msg::Bus& mMessageBus;

  sf::Window mWindow;
};
} // namespace aw::engine
