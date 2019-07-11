#pragma once

#include "shared/ship.hpp"

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
  };

public:
  void addClient(Client*);
  void removeClient(Client*);

  void update(float dt);

private:
  std::vector<ClientShipPair> mPlayers;
  std::mutex mPlayerMutex;

  sf::Packet mGameTick;
};
