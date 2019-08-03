#pragma once

#include "incommingPacket.hpp"
#include "outgoingPacket.hpp"
#include "protocol.hpp"

#include <vector>

namespace network
{
class Channel
{
public:
  bool sendPackage(OutgoingPacket& packet, Command command, TransmissionType transmission);

  void receive(IncommingPacket& packet);

  void update(float dt);

  bool hasAcknowledgesToSend() const { return !mAcknowledgeList.empty(); }
  void sendAcknowledges(OutgoingPacket& packet);

private:
  void onAcknowledgePacket(IncommingPacket& packet);

private:
  aw::uint16 mSendPacketNumber{0};

  std::vector<OutgoingPacket*> mNotAcknoledgedPackets;
  std::vector<IncommingPacket*> mWaitingPackets;
  std::vector<aw::uint16> mAcknowledgeList;
};

} // namespace network
