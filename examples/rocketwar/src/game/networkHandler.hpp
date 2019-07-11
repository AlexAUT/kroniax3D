#pragma once

#include <string>
#include <thread>
#include <vector>

#include <SFML/Network/Packet.hpp>
#include <SFML/Network/TcpSocket.hpp>

#include <aw/util/math/vector.hpp>

class NetworkHandler
{
public:
  NetworkHandler(std::string serverAddress, int port);
  ~NetworkHandler();

  void update(float dt);

  bool connected() const { return mConnected; };

  std::vector<aw::Vec3> shipPositions();
  int shipPositionsVersion() const { return mShipPositionsVersion; }

private:
  void workerThread();

  void tryToConnect();

  void onGameTick(sf::Packet& packet);

private:
  bool mRunning{true};

  bool mTryToConnect{true};
  bool mConnected{false};

  std::string mServerAddress;
  int mPort;

  sf::TcpSocket mSocket;

  std::thread mThread;

  int mShipPositionsVersion{0};
  std::vector<aw::Vec3> mShipPositions;
};
