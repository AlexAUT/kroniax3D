#pragma once

#include <aw/graphics/core/vertexAttribute.hpp>
#include <aw/util/types.hpp>

#include <array>

namespace aw
{
template <size_t N>
using VertexLayout = std::array<VertexAttribute, N>;
}
