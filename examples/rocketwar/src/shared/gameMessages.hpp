#pragma once

#include <aw/util/reflection/typeDescriptorClass.hpp>
#include <aw/util/reflection/types/primitiveTypes.hpp>
#include <aw/util/reflection/types/string.hpp>

#include <aw/util/types.hpp>

#include <string>

#include <SFML/Network/Packet.hpp>

enum class ClientMessages : aw::uint8
{
  Connect,
  Disconnect,
  GetGameList,
};

enum class ServerMessages : aw::uint8
{
  ClientConnected,
};

struct ClientConnect
{
  static constexpr auto type = ClientMessages::Connect;

  std::string name;

  REFLECT()
};

REFLECT_BEGIN(ClientConnect)
REFLECT_MEMBER(name)
REFLECT_END(ClientConnect)

struct ClientConnected
{
  static constexpr auto type = ServerMessages::ClientConnected;

  aw::uint32 id;

  REFLECT()
};
REFLECT_BEGIN(ClientConnected)
REFLECT_MEMBER(id)
REFLECT_END(ClientConnected)

inline sf::Packet& operator<<(sf::Packet& packet, const ClientMessages& type)
{
  using T = std::underlying_type<ClientMessages>::type;
  return packet << static_cast<T>(type);
}

inline sf::Packet& operator>>(sf::Packet& packet, ClientMessages& type)
{
  using T = std::underlying_type<ClientMessages>::type;
  T buffer;
  packet >> buffer;
  type = static_cast<ClientMessages>(buffer);

  return packet;
}

inline sf::Packet& operator<<(sf::Packet& packet, const ServerMessages& type)
{
  using T = std::underlying_type<ServerMessages>::type;
  return packet << static_cast<T>(type);
}

inline sf::Packet& operator>>(sf::Packet& packet, ServerMessages& type)
{
  using T = std::underlying_type<ServerMessages>::type;
  T buffer;
  packet >> buffer;
  type = static_cast<ServerMessages>(buffer);

  return packet;
}

template <typename Message>
Message unzip(sf::Packet& packet)
{
  Message unzipped;

  auto refl = aw::reflect::getReflection<Message>();
  refl.forAllMembers([&](auto member) {
    using MemberType = typename decltype(member)::UnderlyingType;
    MemberType temp;
    packet >> temp;
    member.value(unzipped, temp);
  });

  return unzipped;
}
