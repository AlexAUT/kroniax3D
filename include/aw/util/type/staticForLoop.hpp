#pragma once

#include <functional>
#include <stddef.h>

namespace aw
{
namespace priv
{
template <class Func, std::size_t... Is>
constexpr void staticForImpl(Func&& f, std::index_sequence<Is...>)
{
  (f(std::integral_constant<std::size_t, Is>{}), ...);
}
} // namespace priv

template <std::size_t iterations, class Func>
constexpr void staticFor(Func&& f)
{
  priv::staticForImpl(std::forward<Func>(f), std::make_index_sequence<iterations>{});
}
} // namespace aw
