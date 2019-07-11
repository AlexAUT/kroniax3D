#include "networkHandler.hpp"

#include <aw/util/math/vector.hpp>
#include <aw/util/types.hpp>

#include "shared/gameMessages.hpp"
#include "shared/packetSerializations.hpp"

#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>

#include <iostream>

NetworkHandler::NetworkHandler(std::string serverAddress, int port) :
    mServerAddress{serverAddress},
    mPort{port},
    mThread([this]() { this->workerThread(); })
{
  mSocket.setBlocking(true);
}

NetworkHandler::~NetworkHandler()
{
  mRunning = false;
  if (mThread.joinable())
    mThread.join();
}

void NetworkHandler::update(float dt) {}

void NetworkHandler::workerThread()
{
  std::cout << "Starting network handler thread" << std::endl;
  sf::Packet packet;
  while (mRunning)
  {
    if (mTryToConnect)
    {
      std::cout << "Try to connect" << std::endl;
      mTryToConnect = false;
      if (mSocket.getLocalPort() == 0)
      {
        auto status = mSocket.connect(sf::IpAddress{mServerAddress}, mPort);
        if (status != sf::Socket::Status::Done)
        {
          std::cout << "Could not connect!" << std::endl;
        }
      }
    }

    auto status = mSocket.receive(packet);
    if (status != sf::TcpSocket::Done)
    {
      std::cout << "Connection failed, disconnected!" << std::endl;
      mRunning = false;
      break;
    }

    int type;
    packet >> type;

    switch (static_cast<MessageType>(type))
    {
    case MessageType::GameTick:
      onGameTick(packet);
      break;
    default:
      std::cout << "Packet type not implemented: " << type << "!\n";
    }
  }

  mSocket.disconnect();
}

void NetworkHandler::tryToConnect() {}

void NetworkHandler::onGameTick(sf::Packet& packet)
{
  sf::Uint64 numberOfPlayer;
  packet >> numberOfPlayer;

  for (auto i = 0U; i < numberOfPlayer; i++)
  {
    aw::uint64 clientId;
    aw::Vec3 pos;
    float velocity;
    aw::Vec3 velocityDir;
    packet >> clientId >> pos >> velocity >> velocityDir;
  }

  return;
  auto cacheVersion = mShipPositionsVersion;
  mShipPositionsVersion = -1;
  mShipPositions.clear();

  for (auto i = 0U; i < numberOfPlayer; i++)
  {
    aw::Vec3 pos;
    packet >> pos.x >> pos.y >> pos.z;
    mShipPositions.push_back(pos);
  }
  mShipPositionsVersion = cacheVersion + 1;
}

std::vector<aw::Vec3> NetworkHandler::shipPositions()
{
  return mShipPositions;
}

