#pragma once

// Thanks to http://blog.bitwigglers.org/using-enum-classes-as-type-safe-bitmasks/

#include <type_traits>

template <typename EnumClass>
struct EnableBitMaskOperators
{
  static const bool enable = true;
};

#define ENABLE_BITMASK_OPERATORS(x)                                                                \
  template <>                                                                                      \
  struct EnableBitMaskOperators<x>                                                                 \
  {                                                                                                \
    static const bool enable = true;                                                               \
  };

template <typename EnumClass>
typename std::enable_if<EnableBitMaskOperators<EnumClass>::enable, EnumClass>::type
operator|(EnumClass lhs, EnumClass rhs)
{
  using underlying = typename std::underlying_type<EnumClass>::type;
  return static_cast<EnumClass>(static_cast<underlying>(lhs) | static_cast<underlying>(rhs));
}

template <typename EnumClass>
typename std::enable_if<EnableBitMaskOperators<EnumClass>::enable, EnumClass>::type
operator&(EnumClass lhs, EnumClass rhs)
{
  using underlying = typename std::underlying_type<EnumClass>::type;
  return static_cast<EnumClass>(static_cast<underlying>(lhs) & static_cast<underlying>(rhs));
}

template <typename EnumClass>
typename std::enable_if<EnableBitMaskOperators<EnumClass>::enable, EnumClass>::type
operator^(EnumClass lhs, EnumClass rhs)
{
  using underlying = typename std::underlying_type<EnumClass>::type;
  return static_cast<EnumClass>(static_cast<underlying>(lhs) ^ static_cast<underlying>(rhs));
}

template <typename EnumClass>
typename std::enable_if<EnableBitMaskOperators<EnumClass>::enable, EnumClass>::type
operator~(EnumClass rhs)
{
  using underlying = typename std::underlying_type<EnumClass>::type;
  return static_cast<EnumClass>(~static_cast<underlying>(rhs));
}

template <typename EnumClass>
typename std::enable_if<EnableBitMaskOperators<EnumClass>::enable, EnumClass>::type&
operator|=(EnumClass& lhs, EnumClass rhs)
{
  using underlying = typename std::underlying_type<EnumClass>::type;
  lhs = static_cast<EnumClass>(static_cast<underlying>(lhs) | static_cast<underlying>(rhs));

  return lhs;
}

template <typename EnumClass>
typename std::enable_if<EnableBitMaskOperators<EnumClass>::enable, EnumClass>::type&
operator&=(EnumClass& lhs, EnumClass rhs)
{
  using underlying = typename std::underlying_type<EnumClass>::type;
  lhs = static_cast<EnumClass>(static_cast<underlying>(lhs) & static_cast<underlying>(rhs));

  return lhs;
}

template <typename EnumClass>
typename std::enable_if<EnableBitMaskOperators<EnumClass>::enable, EnumClass>::type&
operator^=(EnumClass& lhs, EnumClass rhs)
{
  using underlying = typename std::underlying_type<EnumClass>::type;
  lhs = static_cast<EnumClass>(static_cast<underlying>(lhs) ^ static_cast<underlying>(rhs));

  return lhs;
}
