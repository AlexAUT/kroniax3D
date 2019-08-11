#pragma once

#include "packet.hpp"
#include "protocol.hpp"

namespace network
{
class OutgoingPacket
{
public:
  static constexpr auto protocolHeaderSize = sizeof(ProtocolHeader);
  static constexpr auto channelHeaderSize = sizeof(ChannelHeader);
  static constexpr auto headerSize = protocolHeaderSize + channelHeaderSize;

public:
  OutgoingPacket();

  void reset();

  void protocolHeader(ProtocolHeader header);
  void channelHeader(ChannelHeader header);

  ProtocolHeader protocolHeader() const { return mProtocolHeader; }
  ChannelHeader channelHeader() const { return mChannelHeader; }

  template <typename Message>
  void zip(Message&& mesage);

  void markForDelivery(size_t maxTries = 1);
  bool markedForDelivery() const { return mDeliverRetries > 0; }

  void acknowledge() { mAcknowledged = true; };
  [[nodiscard]] bool acknowledged() const { return mAcknowledged; }

  const std::vector<aw::uint8>& payload() const { return mPacket.payload(); }

  int onSendAttempt();

  aw::uint16 id() const { return mId; }

  bool inUse() const
  {
    return mDeliverRetries > 0 ||
           (channelHeader().transmission == TransmissionType::Reliable && !acknowledged());
  }

  float timeForDelivery{0.f};

private:
private:
  Packet mPacket;

  bool mAcknowledged{false};
  size_t mDeliverRetries{0};
  aw::uint16 mId;

  ProtocolHeader mProtocolHeader;
  ChannelHeader mChannelHeader;
};
} // namespace network

namespace network
{
template <typename Message>
void OutgoingPacket::zip(Message&& message)
{
  mPacket.zip(message);
}
} // namespace network
