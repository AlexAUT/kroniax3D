#pragma once

#include <aw/util/reflection/reflection.hpp>
#include <aw/util/reflection/typeDescriptorEnum.hpp>
#include <aw/util/reflection/types/vector.hpp>
#include <aw/util/types.hpp>

#include <iostream>
#include <type_traits>
#include <vector>

namespace network
{
class Packet
{
public:
  Packet();

  void clear();
  void resize(size_t bytes);

  void writeToPayload(const void* data, aw::size_t size);

  std::vector<aw::uint8>& payload() { return mPayload; }
  const std::vector<aw::uint8>& payload() const { return mPayload; }

  template <typename Message>
  void zip(Message&& message);

  template <typename Message>
  bool unzip(Message& message);

  bool checkReadSize(size_t bytes);
  size_t readCursor() const { return mReadCursor; }

  size_t writeCursor() { return mWriteCursor; }

  void incrementReadCursor(size_t offset) { mReadCursor += offset; }
  void readCursor(unsigned cursor) { mReadCursor = cursor; }
  void incrementWriteCursor(size_t offset) { mWriteCursor += offset; }
  void writeCursor(unsigned cursor) { mWriteCursor = cursor; }

  operator bool() const { return !mError; }

private:
private:
  std::vector<aw::uint8> mPayload;

  size_t mReadCursor{0};
  size_t mWriteCursor{0};
  bool mError{false};
};

template <typename Message>
void Packet::zip(Message&& message)
{
  auto refl = aw::reflect::getReflection<std::remove_const_t<std::remove_reference_t<Message>>>();
  refl.forAllMembers([&](auto member) {
    using MemberDescriptor = decltype(member);
    using UnderlyingDescriptor = typename MemberDescriptor::UnderlyingDescriptor;
    if constexpr (aw::reflect::isEnum<UnderlyingDescriptor>())
    {
      *this << static_cast<typename UnderlyingDescriptor::UnderlyingType>(member.value(message));
    }
    else if constexpr (aw::reflect::isVector<UnderlyingDescriptor>())
    {
      auto& vector = member.value(message);
      *this << (static_cast<aw::uint64>(vector.size()));
      for (auto& element : vector)
        *this << element;
    }
    else
    {
      *this << member.value(message);
    }
  });
}

template <typename Message>
bool Packet::unzip(Message& message)
{
  auto refl = aw::reflect::getReflection<Message>();
  refl.forAllMembers([&](auto member) {
    using MemberDescriptor = decltype(member);
    using MemberType = typename decltype(member)::UnderlyingType;
    using UnderlyingDescriptor = typename MemberDescriptor::UnderlyingDescriptor;
    if constexpr (aw::reflect::isEnum<UnderlyingDescriptor>())
    {
      MemberType temp;
      *this >> temp;
      using EnumType = typename UnderlyingDescriptor::EnumType;
      member.value(message, static_cast<EnumType>(temp));
    }
    else if constexpr (aw::reflect::isVector<UnderlyingDescriptor>())
    {
      using Vector = typename UnderlyingDescriptor::UnderlyingType;
      using T = typename UnderlyingDescriptor::value_type;
      aw::uint64 size;
      *this >> size;

      Vector vector;
      vector.reserve(size);
      for (int i = 0; i < size; i++)
      {
        T temp;
        *this >> temp;
        vector.push_back(temp);
      }
      member.value(message, vector);
    }
    else
    {
      MemberType temp;
      *this >> temp;
      member.value(message, temp);
    }
  });

  return true;
}

Packet& operator<<(Packet& packet, aw::uint8 value);
Packet& operator<<(Packet& packet, aw::uint16 value);
Packet& operator<<(Packet& packet, aw::uint32 value);
Packet& operator<<(Packet& packet, aw::uint64 value);

Packet& operator<<(Packet& packet, aw::int8 value);
Packet& operator<<(Packet& packet, aw::int16 value);
Packet& operator<<(Packet& packet, aw::int32 value);
Packet& operator<<(Packet& packet, aw::int64 value);

template <typename T>
Packet& operator>>(Packet& packet, T& v);
} // namespace network
