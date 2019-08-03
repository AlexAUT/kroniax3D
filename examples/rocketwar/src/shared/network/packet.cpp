#include "packet.hpp"

#include "conversion.hpp"

#include <cassert>
#include <cstring>

namespace network
{
Packet::Packet()
{
  clear();
}

void Packet::clear()
{
  mPayload.clear();
  mWriteCursor = 0;
  mReadCursor = 0;
  mError = false;
}

void Packet::resize(size_t bytes)
{
  mPayload.resize(bytes);
  mWriteCursor = std::min(mWriteCursor, mPayload.size());
  mReadCursor = std::min(mReadCursor, mPayload.size());
}

void Packet::writeToPayload(const void* data, aw::size_t size)
{
  assert(mPayload.size() >= mWriteCursor);
  if (mPayload.size() < mWriteCursor || mError)
  {
    mError = true;
    return;
  }

  auto spaceLeft = mPayload.size() - mWriteCursor;
  auto diff = spaceLeft >= size ? 0 : size - spaceLeft;

  mPayload.resize(mPayload.size() + diff);
  if (data)
    std::memcpy(mPayload.data() + mWriteCursor, data, size);

  mWriteCursor += size;
}

bool Packet::checkReadSize(size_t bytes)
{
  if (!*this || mError)
    return false;

  if (mReadCursor + bytes > mPayload.size())
  {
    mError = true;
    return false;
  }

  return true;
}

Packet& operator<<(Packet& packet, aw::uint8 value)
{
  packet.writeToPayload(&value, sizeof(value));
  return packet;
}

Packet& operator<<(Packet& packet, aw::uint16 value)
{
  auto conv = toNetworkOder(value);
  packet.writeToPayload(&conv, sizeof(conv));
  return packet;
}

Packet& operator<<(Packet& packet, aw::uint32 value)
{
  auto conv = toNetworkOder(value);
  packet.writeToPayload(&conv, sizeof(conv));
  return packet;
}
Packet& operator<<(Packet& packet, aw::uint64 value)
{
  auto conv = toNetworkOder(value);
  packet.writeToPayload(&conv, sizeof(conv));
  return packet;
}

Packet& operator<<(Packet& packet, aw::int8 value)
{
  packet.writeToPayload(&value, sizeof(value));
  return packet;
}

Packet& operator<<(Packet& packet, aw::int16 value)
{
  auto conv = toNetworkOder(value);
  packet.writeToPayload(&conv, sizeof(conv));
  return packet;
}

Packet& operator<<(Packet& packet, aw::int32 value)
{
  auto conv = toNetworkOder(value);
  packet.writeToPayload(&conv, sizeof(conv));
  return packet;
}

Packet& operator<<(Packet& packet, aw::int64 value)
{
  auto conv = toNetworkOder(value);
  packet.writeToPayload(&conv, sizeof(conv));
  return packet;
}

template <typename T>
void extract(Packet& packet, T& value)
{
  value = *static_cast<const T*>(
      static_cast<const void*>(packet.payload().data() + packet.readCursor()));
}

template <typename T>
Packet& operator>>(Packet& packet, T& v)
{
  constexpr auto size = sizeof(T);
  if (packet.checkReadSize(size))
  {
    extract(packet, v);
    packet.incrementReadCursor(size);
    v = toHostOrder(v);
  }
  return packet;
}

template Packet& operator>>(Packet& packet, aw::uint8& v);
template Packet& operator>>(Packet& packet, aw::uint16& v);
template Packet& operator>>(Packet& packet, aw::uint32& v);
template Packet& operator>>(Packet& packet, aw::uint64& v);
template Packet& operator>>(Packet& packet, aw::int8& v);
template Packet& operator>>(Packet& packet, aw::int16& v);
template Packet& operator>>(Packet& packet, aw::int32& v);
template Packet& operator>>(Packet& packet, aw::int64& v);

} // namespace network
