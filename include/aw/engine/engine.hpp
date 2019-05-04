#pragma once

#include <SFML/Window/Window.hpp>

namespace aw
{
class Engine
{
public:
  Engine();

  int run();

  void step();
private:

private:
  sf::Window mWindow;
};
} // namespace aw
