#pragma once

#include <string>
#include <thread>

#include <SFML/Network/TcpSocket.hpp>

class NetworkHandler
{
public:
  NetworkHandler(std::string serverAddress, int port);
  ~NetworkHandler();

  void update(float dt);

  bool connected() const { return mConnected; };

private:
  void workerThread();

  void tryToConnect();

private:
  bool mRunning{true};

  bool mTryToConnect{true};
  bool mConnected{false};

  std::string mServerAddress;
  int mPort;

  sf::TcpSocket mSocket;

  std::thread mThread;
};
