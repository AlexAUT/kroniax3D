#pragma once

#include <aw/util/types.hpp>

#include <string>

namespace aw
{
using Hash = uint32;

namespace detail
{
// FNV-1a 32bit hashing algorithm.
constexpr Hash fnv1a_32(char const* s, std::size_t count)
{
  return ((count ? fnv1a_32(s, count - 1) : 2166136261u) ^ s[count]) * 16777619u;
}
} // namespace detail

constexpr Hash operator"" _hash(char const* s, std::size_t count)
{
  return detail::fnv1a_32(s, count);
}

constexpr Hash hash(std::string_view view)
{
  return detail::fnv1a_32(view.data(), view.size());
}
} // namespace aw
