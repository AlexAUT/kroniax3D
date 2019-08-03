#pragma once

#include <SFML/Network/Packet.hpp>

#include <aw/util/math/vector.hpp>
#include <aw/util/types.hpp>

inline sf::Packet& operator<<(sf::Packet& packet, const aw::Vec3& vec)
{
  return packet << vec.x << vec.y << vec.z;
}

inline sf::Packet& operator>>(sf::Packet& packet, aw::Vec3& vec)
{
  return packet >> vec.x >> vec.y >> vec.z;
}

inline sf::Packet& operator<<(sf::Packet& packet, const aw::uint64& val)
{
  return packet << val;
}

inline sf::Packet& operator>>(sf::Packet& packet, aw::uint64& val)
{
  return packet >> val;
}

