#pragma once

#include "connection.hpp"
#include "incommingPacket.hpp"
#include "types.hpp"

#include <SFML/Network/UdpSocket.hpp>

#include <vector>

namespace network
{
class Client
{
public:
  bool connect(Ip serverIp, Port serverPort, Port ownPort = anyPort);

  void update(float dt);

private:
  void receiveMessages();

  IncommingPacket& newPacket();

private:
  sf::UdpSocket mSocket;
  Port mPort;

  Connection mConnection;

  std::vector<IncommingPacket> mReceiveBuffer;
};
} // namespace network
