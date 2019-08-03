#pragma once

#include <queue>
#include <vector>

#include "channel.hpp"
#include "protocol.hpp"
#include "types.hpp"

namespace sf
{
class UdpSocket;
}

namespace network
{
class Connection
{
public:
  Connection() = default;
  Connection(Ip peerIp, Port peerPort);

  bool tryConnect(Ip hostIp, Port hostPort);

  bool connected() const { return mConnected; }

  const Ip& ip() const { return mHostIp; }
  Port port() const { return mHostPort; }

  void update(float dt, sf::UdpSocket& socket);

  void receive(IncommingPacket& packet);

private:
  OutgoingPacket& newPacket(ChannelId id);

  void handleManagementPacket(IncommingPacket& packet);

private:
  bool mConnected{false};

  Ip mHostIp;
  Port mHostPort;

  std::unordered_map<ChannelId, Channel> mChannels;

  std::vector<OutgoingPacket> mSendQueue;
};
} // namespace network
