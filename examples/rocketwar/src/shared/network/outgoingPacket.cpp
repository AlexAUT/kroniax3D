#include "outgoingPacket.hpp"

namespace network
{
OutgoingPacket::OutgoingPacket()
{
  reset();
}

void OutgoingPacket::reset()
{
  mPacket.clear();
  // Make room for header
  mPacket.writeToPayload(nullptr, headerSize);

  mAcknowledged = false;
  mDeliverRetries = 0;
}

void OutgoingPacket::protocolHeader(ProtocolHeader header)
{
  auto oldCursor = mPacket.writeCursor();
  mPacket.writeCursor(0);
  mPacket.zip(header);
  mPacket.writeCursor(oldCursor);
}

void OutgoingPacket::channelHeader(ChannelHeader header)
{
  auto cursorOffset = mPacket.writeCursor() - protocolHeaderSize;
  auto oldCursor = mPacket.writeCursor();
  mPacket.writeCursor(protocolHeaderSize);
  mPacket.zip(header);
  mPacket.writeCursor(oldCursor);

  mId = header.packetId;
}

void OutgoingPacket::markForDelivery(size_t maxTries)
{
  mDeliverRetries = maxTries;
}

void OutgoingPacket::acknowledge(bool value)
{
  mAcknowledged = value;
}

void OutgoingPacket::onSendAttempt()
{
  if (mDeliverRetries > 0)
    mDeliverRetries--;
}
} // namespace network
