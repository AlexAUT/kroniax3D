#pragma once

#include <aw/util/types.hpp>

#include <SFML/Network/IpAddress.hpp>

namespace network
{
using Port = aw::uint16;
using Ip = sf::IpAddress;

constexpr Port anyPort = 0;
} // namespace network
