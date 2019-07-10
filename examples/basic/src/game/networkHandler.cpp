#include "networkHandler.hpp"

#include <SFML/Network/IpAddress.hpp>

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
      std::cout << "Connected to server!" << std::endl;
      mRunning = false;
    }
  }
  mSocket.disconnect();
}

void NetworkHandler::tryToConnect() {}

