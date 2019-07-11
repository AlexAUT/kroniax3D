#include "client.hpp"

#include "game.hpp"
#include "server.hpp"
#include "shared/gameMessages.hpp"

#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>

#include <fmt/printf.h>

Client::Client(aw::uint64 clientId) : mClientId(clientId)
{
  mSocket.setBlocking(true);
}

Client::~Client()
{
  mGame->removeClient(this);
  if (std::this_thread::get_id() == mThread.get_id())
    mThread.detach();
  else if (mThread.joinable())
    mThread.join();
}

sf::TcpSocket& Client::socket()
{
  return mSocket;
}

const sf::TcpSocket& Client::socket() const
{
  return mSocket;
}

void Client::start(Server* server, Game* game)
{
  mServer = server;
  mGame = game;

  mGame->addClient(this);

  mThread = std::thread([this]() { this->threadFunc(); });
}

void Client::send(sf::Packet& packet)
{
  mSocket.send(packet);
}

void Client::threadFunc()
{
  auto ip = mSocket.getRemoteAddress().toString();
  fmt::print("Client worker started for: {}\n", ip);

  sf::Packet serverInit;
  serverInit << MessageType::Init;
  mSocket.send(serverInit);

  sf::Packet packet;
  while (mSocket.receive(packet) == sf::TcpSocket::Done)
  {
    MessageType type;
    int t;
    packet >> t;
    type = static_cast<MessageType>(t);

    fmt::print("Received message type {}\n", type);
  }

  fmt::print("Closed connection to client {}\n", ip);

  mServer->onClientDisconnect(this);
}
