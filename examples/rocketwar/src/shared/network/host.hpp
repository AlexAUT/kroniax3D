#pragma once

#include "connection.hpp"
#include "protocol.hpp"
#include "types.hpp"

#include <SFML/Network/UdpSocket.hpp>

#include <vector>

namespace network
{
class Host
{
public:
  Host(Port port);

  void update(float dt);

private:
  void receiveMessages();

  IncommingPacket& newPacket();

private:
  sf::UdpSocket mSocket;
  Port mPort;

  std::vector<Connection> mConnections;

  std::vector<IncommingPacket> mReceiveBuffer;
};
}; // namespace network
