#include "client.hpp"

#include "packet.hpp"
#include "protocol.hpp"

#include <SFML/Network/Packet.hpp>

namespace network
{
bool Client::connect(Ip hostIp, Port hostPort, Port ownPort)
{
  mPort = ownPort == anyPort ? sf::UdpSocket::AnyPort : ownPort;

  mSocket.setBlocking(false);
  auto status = mSocket.bind(mPort);

  if (status != sf::UdpSocket::Done)
    return false;

  if (!mConnection.tryConnect(hostIp, hostPort))
  {
    mSocket.unbind();
    return false;
  }

  return true;
}

void Client::update(float dt)
{
  receiveMessages();

  mConnection.update(dt, mSocket);
}

void Client::receiveMessages()
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

  mConnection.receive(packet);
}

IncommingPacket& Client::newPacket()
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
