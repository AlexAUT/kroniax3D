#include "host.hpp"

#include "packet.hpp"
#include "protocol.hpp"

#include <aw/util/reflection/operators/toStream.hpp>

#include <iostream>

namespace network
{
Host::Host(Port port) : mPort{port}
{
  mSocket.setBlocking(false);
  mSocket.bind(port);
}

void Host::update(float dt)
{
  receiveMessages();

  for (auto& connection : mConnections)
    connection.update(dt, mSocket);
}

void Host::receiveMessages()
{
  Ip ip;
  Port port;

  auto& packet = newPacket();

  size_t received;
  auto status = mSocket.receive(packet.reserve(sf::UdpSocket::MaxDatagramSize),
                                sf::UdpSocket::MaxDatagramSize, received, ip, port);

  if (status != sf::UdpSocket::Done)
  {
    packet.handled(true);
    return;
  }

  packet.resize(received);

  std::cout << "Received message! " << std::endl;
  std::cout << "Message buffer size: " << mReceiveBuffer.size() << std::endl;

  bool handled = false;
  for (auto& connection : mConnections)
  {
    if (port == connection.port() && ip == connection.ip())
    {
      connection.receive(packet);
      handled = true;
      break;
    }
  }

  if (!handled)
  {
    // Else looks like a new connection
    mConnections.emplace_back(ip, port);
    mConnections.back().receive(packet);
    if (!mConnections.back().connected())
    {
      std::cout << "Invalid new host?" << std::endl;
      mConnections.pop_back();
    }
    else
    {
      std::cout << "New connection established: " << mConnections.back().ip().toString() << ":"
                << mConnections.back().port() << std::endl;
    }
  }
}

IncommingPacket& Host::newPacket()
{

  auto found = std::find_if(mReceiveBuffer.begin(), mReceiveBuffer.end(),
                            [](const IncommingPacket& p) { return p.handled(); });

  if (found != mReceiveBuffer.end())
  {
    found->reset();
    return *found;
  }

  mReceiveBuffer.emplace_back();
  return mReceiveBuffer.back();
}

} // namespace network
