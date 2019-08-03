#pragma once

#include <aw/util/types.hpp>

#include <array>
#include <cstring>

namespace network
{
template <typename T>
inline T toNetworkOder(T value)
{
  constexpr bool valid = sizeof(T) == 1 || sizeof(T) == 2 || sizeof(T) == 4 || sizeof(T) == 8;
  static_assert(valid, "Unsupported bytewidth!");

  if constexpr (sizeof(T) == 1)
    return value;
  else if constexpr (sizeof(T) == 2)
    return toNetworkOder(static_cast<aw::uint16>(value));
  else if constexpr (sizeof(T) == 4)
    return toNetworkOder(static_cast<aw::uint32>(value));
  else if constexpr (sizeof(T) == 8)
    return toNetworkOder(static_cast<aw::uint64>(value));
}

template <typename T>
inline T toHostOrder(T value)
{
  constexpr bool valid = sizeof(T) == 1 || sizeof(T) == 2 || sizeof(T) == 4 || sizeof(T) == 8;
  static_assert(valid, "Unsupported bytewidth!");

  if constexpr (sizeof(T) == 1)
    return value;
  else if constexpr (sizeof(T) == 2)
    return toHostOrder(static_cast<aw::uint16>(value));
  else if constexpr (sizeof(T) == 4)
    return toHostOrder(static_cast<aw::uint32>(value));
  else if constexpr (sizeof(T) == 8)
    return toHostOrder(static_cast<aw::uint64>(value));
}

template <>
inline aw::uint16 toNetworkOder(aw::uint16 net)
{
  std::array<aw::uint8, 2> data = {static_cast<aw::uint8>(net >> 8),
                                   static_cast<aw::uint8>(net >> 0)};
  std::memcpy(&net, data.data(), sizeof(data));

  return net;
}

template <>
inline aw::uint32 toNetworkOder(aw::uint32 net)
{
  std::array<aw::uint8, 4> data = {
      static_cast<aw::uint8>(net >> 24), static_cast<aw::uint8>(net >> 16),
      static_cast<aw::uint8>(net >> 8), static_cast<aw::uint8>(net >> 0)};
  std::memcpy(&net, data.data(), sizeof(data));

  return net;
}

template <>
inline aw::uint64 toNetworkOder(aw::uint64 net)
{
  std::array<aw::uint8, 8> data = {
      static_cast<aw::uint8>(net >> 56), static_cast<aw::uint8>(net >> 48),
      static_cast<aw::uint8>(net >> 40), static_cast<aw::uint8>(net >> 32),
      static_cast<aw::uint8>(net >> 24), static_cast<aw::uint8>(net >> 16),
      static_cast<aw::uint8>(net >> 8),  static_cast<aw::uint8>(net >> 0)};
  std::memcpy(&net, data.data(), sizeof(data));

  return net;
}

template <>
inline aw::uint16 toHostOrder(aw::uint16 net)
{
  std::array<aw::uint8, 2> data;
  std::memcpy(data.data(), &net, sizeof(data));

  return ((aw::uint16)data[0] << 0) | ((aw::uint16)data[1] << 8);
}

template <>
inline aw::uint32 toHostOrder(aw::uint32 net)
{
  std::array<aw::uint8, 4> data;
  std::memcpy(data.data(), &net, sizeof(data));

  return ((aw::uint32)data[3] << 0) | ((aw::uint32)data[2] << 8) | ((aw::uint32)data[1] << 16) |
         ((aw::uint32)data[0] << 24);
}

template <>
inline aw::uint64 toHostOrder(aw::uint64 net)
{
  std::array<aw::uint8, 8> data;
  std::memcpy(data.data(), &net, sizeof(data));

  return ((aw::uint64)data[7] << 0) | ((aw::uint64)data[6] << 8) | ((aw::uint64)data[5] << 16) |
         (aw::uint64)data[4] << 24 | ((aw::uint64)data[3] << 32) | ((aw::uint64)data[2] << 40) |
         ((aw::uint64)data[1] << 48) | ((aw::uint64)data[0] << 56);
}

} // namespace network
