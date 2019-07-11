#pragma once

#include <string>
#include <thread>
#include <vector>

#include <SFML/Network/Packet.hpp>
#include <SFML/Network/TcpSocket.hpp>

#include <aw/util/containers/ringBuffer.hpp>
#include <aw/util/math/vector.hpp>

#include "player.hpp"

class BasicState;

class NetworkHandler
{
public:
  NetworkHandler(BasicState& gameState, std::string serverAddress, int port);
  ~NetworkHandler();

  void update(float dt);

  bool connected() const { return mConnected; };

  std::vector<aw::Vec3> shipPositions();
  int shipPositionsVersion() const { return mShipPositionsVersion; }

  aw::RingBuffer<Player, 24> mPlayersToSpawn;
  aw::RingBuffer<aw::uint64, 24> mPlayersToDestroy;

private:
  void workerThread();

  void tryToConnect();

  void onClientInformation(sf::Packet& packet);
  void onClientConnected(sf::Packet& packet);
  void onClientDisconnected(sf::Packet& packet);
  void onGameState(sf::Packet& packet);
  void onShipSpawned(sf::Packet& packet);
  void onGameTick(sf::Packet& packet);

private:
  BasicState& mGameState;

  bool mRunning{true};

  bool mTryToConnect{true};
  bool mConnected{false};

  std::string mServerAddress;
  int mPort;

  sf::TcpSocket mSocket;

  std::thread mThread;

  int mShipPositionsVersion{0};
  std::vector<aw::Vec3> mShipPositions;

  aw::uint64 mClientId{0};
};
