#pragma once

#include <aw/util/types.hpp>

#include <SFML/Network/TcpSocket.hpp>

#include <thread>

class Server;
class Game;

class Client
{
public:
  Client(aw::uint64 ClientId);
  ~Client();

  sf::TcpSocket& socket();
  const sf::TcpSocket& socket() const;

  void start(Server* server, Game* game);
  void send(sf::Packet& packet);

  aw::uint64 id() const { return mClientId; }

private:
  void threadFunc();

private:
  std::thread mThread;

  sf::TcpSocket mSocket;

  Server* mServer;
  Game* mGame;

  aw::uint64 mClientId;
};
