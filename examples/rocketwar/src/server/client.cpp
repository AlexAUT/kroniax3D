#include "client.hpp"

#include "game.hpp"
#include "server.hpp"
#include "shared/gameMessages.hpp"

#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>

#include <fmt/printf.h>

Client::Client(Id id, std::string name, sf::IpAddress ip, unsigned short port) :
    mId(id),
    mName(std::move(name)),
    mAddress(std::move(ip)),
    mPort(port)
{
}

