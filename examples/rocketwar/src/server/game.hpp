#pragma once

#include "shared/ship.hpp"
#include "shared/shipController.hpp"

#include "client.hpp"

#include <SFML/Network/Packet.hpp>

#include <map>
#include <mutex>
#include <vector>

class Game
{
public:
  struct ClientShipPair
  {
    Client* client;
    Ship ship;
    ShipController shipController;
  };

public:
  void addClient(Client* client);
  void removeClient(Client::Id id);

  void update(float dt);

private:
  std::vector<ClientShipPair> mPlayers;
  std::mutex mPlayerMutex;

  sf::Packet mGameTick;
  sf::Packet mClientConnected;
  sf::Packet mShipSpawned;
  sf::Packet mGameState;
  sf::Packet mClientDisconnected;
};
