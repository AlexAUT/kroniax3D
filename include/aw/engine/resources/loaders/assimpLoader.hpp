#pragma once

#include <aw/engine/resources/staticMesh.hpp>

#include <vector>

class aiScene;

namespace aw::engine
{
class StaticMesh;

class AssimpLoader
{
public:
  struct Config
  {
    enum class NormalType
    {
      InhertFromMesh,
      Hard,
      Smooth,
      Discard,
    };

    bool trianglulate{true};
    NormalType normals{NormalType::InhertFromMesh};
  };

public:
  AssimpLoader() = default;
  AssimpLoader(Config config);

  bool load(StaticMesh& mesh, const char* path);

private:
  bool parseMesh(const aiScene* scene, unsigned meshIndex);

private:
  Config mConfig{};

  StaticMesh* mStaticMesh{nullptr};

  StaticMesh::Positions mPositions;
  StaticMesh::Normals mNormals;
  std::vector<StaticMesh::UVChannel> mUVChannels;

  StaticMesh::SubMeshOffsets mSubMeshOffsets;
  StaticMesh::Indices mIndices;
};
} // namespace aw::engine
