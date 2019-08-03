#include "incommingPacket.hpp"

#include <cassert>

namespace network
{
void IncommingPacket::reset()
{
  assert(mHandled && "You are resetting a not handled packet!");

  mPacket.clear();
  mReadPos = 0;
  mHandled = false;
}

aw::uint8* IncommingPacket::reserve(size_t bytes)
{
  mPacket.clear();
  mPacket.writeToPayload(nullptr, bytes);

  return mPacket.payload().data();
}

void IncommingPacket::resize(size_t bytes)
{
  mPacket.resize(bytes);
}
} // namespace network
