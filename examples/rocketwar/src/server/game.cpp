#include "game.hpp"

#include <fmt/printf.h>

#include "shared/gameMessages.hpp"
#include "shared/packetSerializations.hpp"

#include <aw/util/serialization/serializeReflectedType.hpp>

float offset = 0.f;

void Game::addClient(Client* client)
{
  auto lock = std::lock_guard(mPlayerMutex);

  mPlayers.push_back({client, {}});
  mPlayers.back().ship.transform().position({offset, 1.25f, -1.f});
  mPlayers.back().ship.velocity(mPlayers.size() + 2);
  offset += 0.5f;

  fmt::print("Added player, player count {}", mPlayers.size());
}

void Game::removeClient(Client* client)
{
  auto lock = std::lock_guard(mPlayerMutex);

  for (auto it = mPlayers.begin(); it != mPlayers.end(); it++)
  {
    if (it->client == client)
    {
      mPlayers.erase(it);
      break;
    }
  }

  fmt::print("Removed player, player count {}", mPlayers.size());
}

class SFMLPacketSerializer
{
public:
  SFMLPacketSerializer(sf::Packet& packet) : mPacket{packet} {}

  void startNode() {}
  void finishNode() {}

  void setNextName(std::string_view) {}

  template <typename T>
  void operator()(const T& t)
  {
    std::cout << "Insert: " << t;
    mPacket << t;
  }

private:
  sf::Packet& mPacket;
};

void Game::update(float dt)
{
  auto lock = std::lock_guard(mPlayerMutex);

  mGameTick.clear();
  mGameTick << MessageType::GameTick;
  mGameTick << static_cast<sf::Uint64>(mPlayers.size());

  SFMLPacketSerializer archive(mGameTick);
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
