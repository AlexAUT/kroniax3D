#pragma once

#include <aw/engine/resources/staticMesh.hpp>

#include <vector>

namespace ofbx
{
class IScene;
}

namespace aw::engine
{
class StaticMesh;

class OFBXLoader
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
  OFBXLoader() = default;
  OFBXLoader(Config config);

  bool load(StaticMesh& mesh, const char* path);

private:
  bool parseMesh(ofbx::IScene* scene, int index);

  bool parseMaterial();

private:
  Config mConfig{};

  StaticMesh* mStaticMesh{nullptr};

  StaticMesh::Materials mMaterials;

  StaticMesh::Positions mPositions;
  StaticMesh::Normals mNormals;
  std::vector<StaticMesh::UVChannel> mUVChannels;

  StaticMesh::Indices mIndices;
  StaticMesh::SubMeshes mSubMeshes;
};
} // namespace aw::engine
