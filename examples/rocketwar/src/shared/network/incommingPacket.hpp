#pragma once

#include <aw/util/types.hpp>

#include "packet.hpp"
#include "protocol.hpp"

namespace network
{
class IncommingPacket
{
public:
  void reset();

  aw::uint8* reserve(size_t bytes);
  void resize(size_t bytes);

  template <typename Message>
  bool unzip(Message& mesage, bool modifyCursor = true);

  const std::vector<aw::uint8>& payload() const { return mPacket.payload(); }

  void handled(bool value) { mHandled = value; }
  bool handled() const { return mHandled; }

  operator bool() const { return mPacket; }

private:
  Packet mPacket;

  size_t mReadPos{0};
  bool mHandled{false};
};
} // namespace network

namespace network
{
template <typename Message>
bool IncommingPacket::unzip(Message& message, bool modifyCursor)
{
  auto readCursor = mPacket.readCursor();
  auto result = mPacket.unzip(message);

  if (!modifyCursor)
    mPacket.incrementReadCursor(readCursor - mPacket.readCursor());

  return result;
}
} // namespace network
