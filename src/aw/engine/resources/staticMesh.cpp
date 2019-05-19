#include <aw/engine/resources/staticMesh.hpp>

#include <aw/opengl/opengl.hpp>

namespace aw::engine
{
void StaticMesh::setPositions(Positions positions)
{
  mPositions = std::move(positions);
}

void StaticMesh::setNormals(Normals normals)
{
  mNormals = std::move(normals);
}

size_t StaticMesh::addUVChannel(UVChannel channel)
{
  mUVChannels.push_back(std::move(channel));
  return mUVChannels.size() - 1;
}

void StaticMesh::setUVChannel(size_t index, UVChannel channel)
{
  assert(numUVChannels() > index);
  mUVChannels[index] = std::move(channel);
}

void StaticMesh::setIndices(Indices indices)
{
  mIndices = std::move(indices);
}

size_t StaticMesh::numUVChannels() const
{
  return mUVChannels.size();
}

auto StaticMesh::positions() const -> const Positions&
{
  return mPositions;
}

auto StaticMesh::normals() const -> const Normals&
{
  return mNormals;
}

auto StaticMesh::uvChannel(size_t index) -> const UVChannel&
{
  assert(numUVChannels() > index);
  return mUVChannels[index];
}

void StaticMesh::update()
{
  const auto hasPositions = !mPositions.empty();
  const auto hasNormals = !mNormals.empty();

  mVAO.bind();

  size_t size = 0;
  if (hasPositions)
    size += mPositions.size() * sizeof(Positions::value_type);
  if (hasNormals)
    size += mNormals.size() * sizeof(Positions::value_type);
  for (auto& channel : mUVChannels)
    size += channel.size() * sizeof(UVChannel::value_type);

  mVBO.bind();

  mVBO.setData(nullptr, size);

  ptrdiff offset = 0;

  if (hasPositions)
  {
    mVBO.setSubData(mPositions, offset);
    offset += mPositions.size() * sizeof(Positions::value_type);
    mVAO.addVertexAttribute(&mVBO,
                            {1, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<const void*>(offset)});
  }
  if (hasNormals)
  {
    mVBO.setSubData(mNormals, offset);
    offset += mNormals.size() * sizeof(Positions::value_type);
    mVAO.addVertexAttribute(&mVBO,
                            {2, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<const void*>(offset)});
  }

  for (auto& channel : mUVChannels)
  {
    mVBO.setSubData(channel, offset);
    offset += channel.size() * sizeof(UVChannel::value_type);
    mVAO.addVertexAttribute(&mVBO,
                            {6, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<const void*>(offset)});
  }
  assert(static_cast<size_t>(offset) == size);

  if (!mIndices.empty())
  {
    mIBO.bind();
    mIBO.setData(mIndices);
  }

  mVAO.unbind();

  mVBO.unbind();
  if (!mIndices.empty())
    mIBO.unbind();
}
} // namespace aw::engine
