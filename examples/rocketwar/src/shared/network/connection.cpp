#include "connection.hpp"

#include "packet.hpp"
#include "protocol.hpp"

#include <aw/util/reflection/operators/toStream.hpp>

#include <SFML/Network/UdpSocket.hpp>

namespace network
{
Connection::Connection(Ip peerIp, Port peerPort) : mHostIp(peerIp), mHostPort(peerPort) {}

bool Connection::tryConnect(Ip hostIp, Port hostPort)
{

  if (mConnected)
    return false;

  mHostIp = hostIp;
  mHostPort = hostPort;

  auto& packet = newPacket(ManagementChannelId);

  return mChannels[ManagementChannelId].sendPackage(packet, Command::Connect,
                                                    TransmissionType::Reliable);
}

void Connection::update(float dt, sf::UdpSocket& socket)
{
  for (auto it = mSendQueue.begin(); it != mSendQueue.end(); it++)
  {
    auto& packet = *it;

    if (packet.markedForDelivery())
    {
      std::cout << "send packet!" << std::endl;
      packet.onSendAttempt();
      socket.send(packet.payload().data(), packet.payload().size(), mHostIp, mHostPort);
    }
  }

  // Send akn
  for (auto& [channelId, channel] : mChannels)
  {
    if (channel.hasAcknowledgesToSend())
      channel.sendAcknowledges(newPacket(channelId));
  }
}

void Connection::receive(IncommingPacket& packet)
{
  ProtocolHeader pHeader;
  packet.unzip(pHeader);

  std::cout << "Incomming channel header: \n";
  aw::reflect::toStream(std::cout, pHeader);

  if (pHeader.channelId == ManagementChannelId)
  {
    handleManagementPacket(packet);
  }

  mChannels[pHeader.channelId].receive(packet);
}

void Connection::handleManagementPacket(IncommingPacket& packet)
{
  ChannelHeader header;
  packet.unzip(header, false);

  switch (header.command)
  {
  case Command::Connect:
    mConnected = true;
    break;
  case Command::Acknowledge:
    if (header.packetId == 0)
      mConnected = true;
    break;
  default:
    std::cout << "Management command not implemented: " << static_cast<int>(header.command)
              << std::endl;
  }
}

OutgoingPacket& Connection::newPacket(ChannelId id)
{
  OutgoingPacket* packet = nullptr;

  auto found = std::find_if(mSendQueue.begin(), mSendQueue.end(),
                            [](const OutgoingPacket& p) { return p.acknowledge(); });

  if (found != mSendQueue.end())
  {
    found->reset();
    packet = &*found;
    std::cout << "Reuse!" << std::endl;
  }
  else
  {
    packet = &mSendQueue.emplace_back();
  }

  ProtocolHeader protHeader;
  protHeader.channelId = ManagementChannelId;

  packet->protocolHeader(protHeader);

  return *packet;
}

} // namespace network
