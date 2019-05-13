#pragma once

#include <aw/graphics/core/bufferObject.hpp>
#include <aw/graphics/core/vertexArrayObject.hpp>
#include <aw/util/math/vector.hpp>
#include <aw/util/types.hpp>

#include <vector>

namespace aw::engine
{
class StaticMesh
{
public:
  using Positions = std::vector<aw::Vec3>;
  using Normals = std::vector<aw::Vec3>;
  using UVChannel = std::vector<aw::Vec2>;
  using Indices = std::vector<uint32>;

public:
  // Those are on purpose by value, because normally you will only set them once
  void setPositions(Positions positions);
  void setNormals(Normals normals);
  size_t addUVChannel(UVChannel channel);
  void setUVChannel(size_t index, UVChannel);
  void setIndices(Indices indices);

  size_t numUVChannels() const;

  const Positions& positions() const;
  const Normals& normals() const;
  const UVChannel& uvChannel(size_t index);

  // This function will generate the GPU buffers
  void update();

private:
private:
  Positions mPositions;
  Normals mNormals;
  std::vector<UVChannel> mUVChannels;

  Indices mIndices;

  gpu::VertexArrayObject mVAO;
  gpu::BufferObject mVBO{gpu::BindType::ArrayBuffer};
  gpu::BufferObject mIBO{gpu::BindType::ElementArrayBuffer};
};
} // namespace aw::engine
