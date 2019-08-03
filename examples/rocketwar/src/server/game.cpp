#include "game.hpp"

#include <fmt/printf.h>

#include "shared/gameMessages.hpp"
#include "shared/packetSerializations.hpp"

float offset = 0.f;

void Game::addClient(Client* client)
{
  auto lock = std::lock_guard(mPlayerMutex);
}

void Game::removeClient(Client::Id clientId) {}

void Game::update(float dt) {}
