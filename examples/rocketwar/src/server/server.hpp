#pragma once

#include "client.hpp"

#include "game.hpp"
#include "shared/gameMessages.hpp"

#include <memory>
#include <mutex>
#include <thread>
#include <vector>

#include "shared/network/host.hpp"

class Server
{
public:
  Server(network::Port port);
  ~Server();

  bool run();

private:
  void gameThreadFunc();

  void onClientConnect(ClientConnect message, sf::IpAddress ip, unsigned short port);
  void onClientDisconnect(sf::Packet& packet, const sf::IpAddress& ip, unsigned short port);

private:
  template <typename Message>
  void send(const sf::IpAddress& address, unsigned short port, Message&& msg);

private:
  bool mRunning{true};

  network::Host mHost;

  std::vector<Client> mClients;
  std::mutex mClientsLock;

  sf::Packet mSendBuffer;

  std::thread mGameThread;

  Game mGame;
};
