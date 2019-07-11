#include "server.hpp"

#include "shared/gameMessages.hpp"
#include "shared/packetSerializations.hpp"

#include <iostream>

#include <aw/util/time/clock.hpp>

#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/TcpSocket.hpp>

#include <fmt/printf.h>

Server::Server()
{
  mGameThread = std::thread([this]() { this->gameThreadFunc(); });
}

Server::~Server()
{
  auto lock = std::lock_guard(mClientsLock);

  while (!mClients.empty())
  {
    mClients.pop_back();
  }
}

bool Server::run(int port)
{
  sf::TcpListener listener;
  listener.setBlocking(true);
  listener.listen(port);
  fmt::print("Listening on PORT {} for new connections\n", port);

  aw::uint64 clientIds = 1;

  while (mRunning)
  {
    auto client = std::make_unique<Client>(clientIds++);
    sf::TcpSocket socket;
    auto status = listener.accept(client->socket());

    if (status != sf::Socket::Status::Done)
    {
      fmt::print("Client connection failed?\n");
      continue;
    }
    fmt::print("Client connected: {}\n", socket.getRemoteAddress().toString());

    sf::Packet packet;
    packet << static_cast<int>(MessageType::ClientInformation);
    packet << client->id();
    client->send(packet);

    auto lock = std::lock_guard(mClientsLock);
    mClients.push_back(std::move(client));
    mClients.back()->start(this, &mGame);
  }

  listener.close();
  mRunning = false;

  return true;
}

void Server::gameThreadFunc()
{
  const float TICK_RATE = 1.f / 30.f;

  aw::Clock clock;
  while (mRunning)
  {
    clock.restart();
    mGame.update(TICK_RATE);

    auto updateTime = clock.restart();

    if (updateTime < TICK_RATE)
    {
      std::this_thread::sleep_for(
          std::chrono::milliseconds(static_cast<int>((TICK_RATE - updateTime) * 1000)));
    }
  }
}

void Server::onClientDisconnect(Client* client)
{
  auto lock = std::lock_guard(mClientsLock);
  for (auto it = mClients.begin(); it != mClients.end(); it++)
  {
    if (it->get() == client)
    {
      mClients.erase(it);
      break;
    }
  }
}
