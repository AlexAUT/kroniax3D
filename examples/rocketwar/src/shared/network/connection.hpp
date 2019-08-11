#pragma once

#include <queue>
#include <vector>

#include "channel.hpp"
#include "connectionMetrics.hpp"
#include "protocol.hpp"
#include "types.hpp"

#include <aw/util/time/time.hpp>

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
  void disconnect();

  bool connected() const { return mConnected; }

  const Ip& ip() const { return mHostIp; }
  Port port() const { return mHostPort; }

  void update(float dt, sf::UdpSocket& socket);

  void receive(IncommingPacket& packet);

private:
  OutgoingPacket& newPacket(ChannelId id);

  void handleManagementPacket(IncommingPacket& packet);

private:
  float mConnectionTime{0.f};
  bool mConnected{false};

  Ip mHostIp;
  Port mHostPort;

  ConnectionMetrics mMetrics;

  std::unordered_map<ChannelId, Channel> mChannels;

  std::vector<OutgoingPacket> mOutgoingPackets;
};
} // namespace network
