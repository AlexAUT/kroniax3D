#include <aw/engine/resources/staticMesh.hpp>

#include <aw/opengl/opengl.hpp>

namespace aw::engine
{
void StaticMesh::positions(Positions positions)
{
  mPositions = std::move(positions);
}

void StaticMesh::normals(Normals normals)
{
  mNormals = std::move(normals);
}

size_t StaticMesh::addUVChannel(UVChannel channel)
{
  mUVChannels.push_back(std::move(channel));
  return mUVChannels.size() - 1;
}

void StaticMesh::uvChannel(size_t index, UVChannel channel)
{
  assert(numUVChannels() > index);
  mUVChannels[index] = std::move(channel);
}

void StaticMesh::uvChannels(std::vector<UVChannel> channels)
{
  mUVChannels = std::move(channels);
}

void StaticMesh::indices(Indices indices)
{
  mIndices = std::move(indices);
}

void StaticMesh::materials(Materials materials)
{
  mMaterials = std::move(materials);
}

void StaticMesh::subMeshes(SubMeshes subMeshes)
{
  mSubMeshes = std::move(subMeshes);
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

auto StaticMesh::uvChannel(size_t index) const -> const UVChannel&
{
  assert(index < numUVChannels());
  return mUVChannels[index];
}

auto StaticMesh::materials() const -> const Materials&
{
  return mMaterials;
}

auto StaticMesh::subMeshes() const -> const SubMeshes&
{
  return mSubMeshes;
}

auto StaticMesh::indices() const -> const Indices&
{
  return mIndices;
}

graphics::Transform& StaticMesh::transform()
{
  return mTransform;
}

const graphics::Transform& StaticMesh::transform() const
{
  return mTransform;
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
    mVAO.addVertexAttribute(&mVBO,
                            {0, 3, GL_FLOAT, GL_TRUE, 0, reinterpret_cast<const void*>(offset)});
    offset += mPositions.size() * sizeof(Positions::value_type);
  }
  if (hasNormals)
  {
    mVBO.setSubData(mNormals, offset);
    mVAO.addVertexAttribute(&mVBO,
                            {1, 3, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<const void*>(offset)});
    offset += mNormals.size() * sizeof(Positions::value_type);
  }

  for (auto i = 0U; i < mUVChannels.size(); i++)
  {
    const auto& channel = mUVChannels[i];

    mVBO.setSubData(channel, offset);
    mVAO.addVertexAttribute(
        &mVBO, {6 + i, 2, GL_FLOAT, GL_FALSE, 0, reinterpret_cast<const void*>(offset)});
    offset += channel.size() * sizeof(UVChannel::value_type);
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

void StaticMesh::bind()
{
  mVAO.bind();
}
} // namespace aw::engine
