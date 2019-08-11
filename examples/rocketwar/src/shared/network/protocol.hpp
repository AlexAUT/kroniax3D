#pragma once

#include "packet.hpp"

#include <aw/util/types.hpp>

#include <aw/util/reflection/typeDescriptorClass.hpp>
#include <aw/util/reflection/typeDescriptorEnum.hpp>
#include <aw/util/reflection/types/primitiveTypes.hpp>
#include <aw/util/reflection/types/vector.hpp>
#include <aw/util/type/bitwiseEnum.hpp>

namespace network
{
enum class Command : aw::uint8
{
  Connect = 1,
  Acknowledge = 2,
  Disconnect = 4,
};

enum class TransmissionType : aw::uint8
{
  Unreliable = 1,
  Reliable = 2,
};

using ChannelId = aw::uint8;

// This channel is used for connection management. You should avoid using it for anything else
inline constexpr aw::uint8 ManagementChannelId = 0xFF;

struct ProtocolHeader
{
  aw::uint8 channelId;

  REFLECT();
};

struct ChannelHeader
{
  Command command;
  TransmissionType transmission;
  aw::uint16 packetId;

  REFLECT()
};

namespace packet
{
struct Acknowledge
{
  std::vector<aw::uint16> packetIds;

  REFLECT()
};
} // namespace packet

} // namespace network

REFLECT_ENUM(network::Command)
REFLECT_ENUM(network::TransmissionType)

REFLECT_BEGIN(network::ProtocolHeader)
REFLECT_MEMBER(channelId)
REFLECT_END(network::ProtocolHeader)

REFLECT_BEGIN(network::ChannelHeader)
REFLECT_MEMBER(command)
REFLECT_MEMBER(transmission)
REFLECT_MEMBER(packetId)
REFLECT_END(network::ChannelHeader)

REFLECT_BEGIN(network::packet::Acknowledge)
REFLECT_MEMBER(packetIds)
REFLECT_END(network::packet::Acknowledge)
