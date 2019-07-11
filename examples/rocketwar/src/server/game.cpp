#include "game.hpp"

#include <fmt/printf.h>

#include "shared/gameMessages.hpp"
#include "shared/packetSerializations.hpp"

float offset = 0.f;

void Game::addClient(Client* client)
{
  auto lock = std::lock_guard(mPlayerMutex);

  mGameState.clear();
  mGameState << MessageType::GameState;
  mGameState << mPlayers.size();
  for (auto& player : mPlayers)
  {
    mGameState << player.client->id();
    mGameState << player.ship.transform().position();
    mGameState << player.ship.velocity();
    mGameState << player.ship.velocityDir();
  }

  mPlayers.push_back({client, {}, {}});
  mPlayers.back().ship.transform().position({offset, 1.25f, -1.f});
  mPlayers.back().ship.velocity(2.f);
  mPlayers.back().ship.velocityDir(aw::Vec3{0.f, 0.f, -1.f});
  mPlayers.back().shipController.setShip(&mPlayers.back().ship);
  mPlayers.back().shipController.update(0.f);

  offset += 0.5f;

  fmt::print("Added player, player count {}", mPlayers.size());
  fmt::print("Packet size: {}", mClientConnected.getDataSize());

  auto& ship = mPlayers.back().ship;

  mShipSpawned.clear();
  mShipSpawned << MessageType::ShipSpawned;
  mShipSpawned << mPlayers.back().client->id();
  mShipSpawned << ship.transform().position();
  mShipSpawned << ship.velocity();
  mShipSpawned << ship.velocityDir();

  for (auto& player : mPlayers)
  {
    player.client->send(mClientConnected);

    if (player.client == client)
    {
      player.client->send(mGameState);
    }
    player.client->send(mShipSpawned);
  }
}

void Game::removeClient(Client* client)
{
  auto lock = std::lock_guard(mPlayerMutex);

  bool deleted = false;
  for (auto it = mPlayers.begin(); it != mPlayers.end(); it++)
  {
    if (it->client == client)
    {
      mPlayers.erase(it);
      deleted = true;
      break;
    }
  }

  if (deleted)
  {
    mClientDisconnected.clear();
    mClientDisconnected << MessageType::ClientDisconnected;
    mClientDisconnected << client->id();

    for (auto player : mPlayers)
      player.client->send(mClientDisconnected);

    fmt::print("Removed player, player count {}", mPlayers.size());
  }
}

void Game::update(float dt)
{
  auto lock = std::lock_guard(mPlayerMutex);

  for (auto& player : mPlayers)
  {
    player.ship.update(dt);
  }

  mGameTick.clear();
  mGameTick << MessageType::GameTick;
  mGameTick << static_cast<sf::Uint64>(mPlayers.size());

  for (auto& player : mPlayers)
  {
    auto& t = player.ship.transform();
    mGameTick << player.client->id();
    mGameTick << t.position();
    mGameTick << player.ship.velocity();
    mGameTick << player.ship.velocityDir();
  }

  for (auto& player : mPlayers)
  {
    player.client->send(mGameTick);
  }
}
