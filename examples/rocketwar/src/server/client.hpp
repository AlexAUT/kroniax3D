#pragma once

#include <aw/util/types.hpp>

#include <SFML/Network/IpAddress.hpp>

#include <string>

class Server;
class Game;

class Client
{
public:
  using Id = aw::uint32;

public:
  Client(Id id, std::string name, sf::IpAddress address, unsigned short port);

  Id id() const { return mId; }
  const std::string& name() const { return mName; }
  const sf::IpAddress address() const { return mAddress; }
  unsigned short port() const { return mPort; }

private:
  Id mId;
  std::string mName;
  sf::IpAddress mAddress;
  unsigned short mPort;
};
