#include "networkHandler.hpp"

#include "basicState.hpp"

#include <aw/util/math/vector.hpp>
#include <aw/util/types.hpp>

#include "shared/gameMessages.hpp"
#include "shared/packetSerializations.hpp"

#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>

#include <iostream>

NetworkHandler::NetworkHandler(BasicState& gameState, std::string serverAddress, int port) :
    mGameState(gameState),
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
    case MessageType::ClientInformation:
      onClientInformation(packet);
      break;
    case MessageType::ShipSpawned:
      onShipSpawned(packet);
      break;
    case MessageType::ClientConnected:
      onClientConnected(packet);
      break;
    case MessageType::ClientDisconnected:
      onClientDisconnected(packet);
      break;
    case MessageType::GameState:
      onGameState(packet);
      break;
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

void NetworkHandler::onClientInformation(sf::Packet& packet)
{
  packet >> mClientId;
}

void NetworkHandler::onClientConnected(sf::Packet& packet) {}

void NetworkHandler::onShipSpawned(sf::Packet& packet)
{
  aw::uint64 clientId;
  aw::Vec3 pos;
  float velocity;
  aw::Vec3 velocityDir;
  packet >> clientId >> pos >> velocity >> velocityDir;

  Player player(clientId);
  player.ship().transform().position(pos);
  player.ship().velocity(velocity);
  player.ship().velocityDir(velocityDir);

  mPlayersToSpawn.put(player);
}

void NetworkHandler::onClientDisconnected(sf::Packet& packet)
{
  aw::uint64 clientId;
  packet >> clientId;
  mPlayersToDestroy.put(clientId);
}

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

void NetworkHandler::onGameState(sf::Packet& packet)
{
  size_t numberOfPlayers;
  packet >> numberOfPlayers;

  std::cout << "On Gamestate: " << numberOfPlayers << std::endl;

  aw::uint64 clientId;
  aw::Vec3 pos;
  float velocity;
  aw::Vec3 velocityDir;
  for (size_t i = 0; i < numberOfPlayers; i++)
  {
    packet >> clientId >> pos >> velocity >> velocityDir;

    Player player(clientId);
    player.ship().transform().position(pos);
    player.ship().velocity(velocity);
    player.ship().velocityDir(velocityDir);

    mPlayersToSpawn.put(player);
  }
}

std::vector<aw::Vec3> NetworkHandler::shipPositions()
{
  return mShipPositions;
}

