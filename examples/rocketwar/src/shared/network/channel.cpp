#include "channel.hpp"

#include "protocol.hpp"

#include <iostream>

#include <aw/util/reflection/operators/toStream.hpp>

namespace network
{
bool Channel::sendPackage(OutgoingPacket& packet, Command command, TransmissionType transmission)
{
  ChannelHeader header;
  header.command = command;
  header.transmission = transmission;
  header.packetId = mSendPacketNumber++;

  packet.channelHeader(header);
  packet.markForDelivery();

  if (transmission == TransmissionType::Reliable)
    mNotAcknoledgedPackets.push_back(&packet);

  return true;
}

void Channel::receive(IncommingPacket& packet)
{
  ChannelHeader header;
  packet.unzip(header);

  aw::reflect::toStream(std::cout, header);

  if (!packet)
  {
    std::cout << "Invalid package in channel!" << std::endl;
    return;
  }

  if (header.transmission == TransmissionType::Reliable)
  {
    mAcknowledge.packetIds.push_back(header.packetId);
  }

  switch (header.command)
  {
  case Command::Connect:
    break;
  case Command::Acknowledge:
    onAcknowledgePacket(packet);
    break;
  default:
    std::cout << "Unsupported command found in package: " << static_cast<int>(header.command)
              << std::endl;
  }

  packet.handled(true);
}

void Channel::update(float dt) {}

void Channel::sendAcknowledges(OutgoingPacket& packet)
{
  if (!mAcknowledge.packetIds.empty())
  {
    packet.zip(mAcknowledge);
    auto result = sendPackage(packet, Command::Acknowledge, TransmissionType::Unreliable);
    if (result)
      mAcknowledge.packetIds.clear();
  }
}

void Channel::onAcknowledgePacket(IncommingPacket& packet)
{
  packet.unzip(mIncommingAcknowledge);

  for (auto& packetId : mIncommingAcknowledge.packetIds)
  {
    for (auto packet : mNotAcknoledgedPackets)
    {
      if (packet->id() == packetId)
      {
        packet->acknowledge();
        std::cout << "Akn " << packetId << std::endl;
      }
    }
  }
}
} // namespace network
