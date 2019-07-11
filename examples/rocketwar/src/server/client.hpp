#pragma once

#include <SFML/Network/TcpSocket.hpp>

#include <thread>

class Server;
class Game;

class Client
{
public:
  Client(int ClientId);
  ~Client();

  sf::TcpSocket& socket();
  const sf::TcpSocket& socket() const;

  void start(Server* server, Game* game);
  void send(sf::Packet& packet);

  int id() const { return mClientId; }

private:
  void threadFunc();

private:
  std::thread mThread;

  sf::TcpSocket mSocket;

  Server* mServer;
  Game* mGame;

  int mClientId;
};
