#include "server.hpp"

#include "shared/gameMessages.hpp"
#include "shared/packetSerializations.hpp"

#include <iostream>

#include <aw/util/time/clock.hpp>

#include <fmt/printf.h>

Server::Server(network::Port port) : mHost(port)
{
  mGameThread = std::thread([this]() { this->gameThreadFunc(); });
}

Server::~Server()
{
  mRunning = false;

  auto lock = std::lock_guard(mClientsLock);

  while (!mClients.empty())
  {
    mClients.pop_back();
  }

  if (mGameThread.joinable())
    mGameThread.join();
}

bool Server::run()
{
  while (mRunning)
  {
    mHost.update(0);

    std::this_thread::sleep_for(std::chrono::milliseconds(20));
  }
  /*
    mSocket.setBlocking(true);
    auto bindStatus = mSocket.bind(port);
    if (bindStatus != sf::UdpSocket::Status::Done)
    {
      fmt::print("Failed to bind listening port {}\n", port);
      return false;
    }

    fmt::print("Listening on PORT {} for new connections\n", port);

    aw::uint64 clientIds = 1;

    sf::Packet receiveBuffer;
    sf::IpAddress senderIp;
    unsigned short senderPort;

    while (mRunning)
    {
      auto status = mSocket.receive(receiveBuffer, senderIp, senderPort);

      if (status != sf::Socket::Status::Done)
      {
        fmt::print("Message failed?\n");
        continue;
      }

      ClientMessages messageType;
      receiveBuffer >> messageType;

      switch (messageType)
      {
      case ClientMessages::Connect:
        onClientConnect(unzip<ClientConnect>(receiveBuffer), senderIp, senderPort);
        break;
      default:
        fmt::print("Unsupported message type {}\n",
                   static_cast<std::underlying_type<ClientMessages>::type>(messageType));
        break;
      }
    }

    mSocket.unbind();
    mRunning = false;
    */
  return true;
}

void Server::gameThreadFunc()
{
  const float TICK_RATE = 1.f / 8.f;

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

void Server::onClientConnect(ClientConnect message, sf::IpAddress ip, unsigned short port)
{
  static aw::uint32 clientId = 0;
  auto lock = std::lock_guard(mClientsLock);

  std::cout << "Client connect: " << message.name << " " << ip.toString() << ":" << port
            << std::endl;

  mClients.emplace_back(++clientId, std::move(message.name), std::move(ip), port);

  send(ip, port, ClientConnected{clientId});
}

void Server::onClientDisconnect(sf::Packet& packet, const sf::IpAddress& ip, unsigned short port) {}

template <typename Message>
void Server::send(const sf::IpAddress& address, unsigned short port, Message&& msg)
{
  mSendBuffer.clear();
  mSendBuffer << Message::type;

  auto refl = aw::reflect::getReflection<Message>();
  refl.forAllMembers([&](auto& member) { mSendBuffer << member.value(msg); });

  //  mSocket.send(mSendBuffer, address, port);
}
