#pragma once

#include <aw/graphics/core/bufferObject.hpp>

namespace aw
{

struct VertexAttribute
{
  unsigned index;
  int size;
  unsigned type;
  bool normalized;
  int stride;
  const void* offset;
};

} // namespace aw
