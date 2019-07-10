#include <aw/engine/resources/loaders/ofbxLoader.hpp>

#include "impl/ofbx/ofbx.h"

#include <aw/util/file/converters.hpp>
#include <aw/util/file/inputStream.hpp>
#include <aw/util/log/log.hpp>

namespace aw::log
{
inline Module assimpLogModule("OFBXLoader");
}

#define LOG_E(...)                                                                                 \
  aw::log::getDefaultLogger()->log(aw::log::assimpLogModule, __FILE__, __LINE__, __func__,         \
                                   aw::log::Level::Error, __VA_ARGS__);
#define LOG_W(...)                                                                                 \
  aw::log::getDefaultLogger()->log(aw::log::assimpLogModule, __FILE__, __LINE__, __func__,         \
                                   aw::log::Level::Warning, __VA_ARGS__);
#define LOG_D(...)                                                                                 \
  aw::log::getDefaultLogger()->log(aw::log::assimpLogModule, __FILE__, __LINE__, __func__,         \
                                   aw::log::Level::Debug, __VA_ARGS__);

namespace aw::engine
{
OFBXLoader::OFBXLoader(Config config) : mConfig(config) {}

bool OFBXLoader::load(StaticMesh& mesh, const char* path)
{
  mMaterials.clear();
  mPositions.clear();
  mNormals.clear();
  mUVChannels.clear();
  mIndices.clear();
  mSubMeshes.clear();

  mStaticMesh = &mesh;

  aw::file::InputStream file(path);

  if (!file.isOpen())
  {
    LOG_D("Failed to open mesh file: {}\n", path);
    return false;
  }

  auto fileContent = aw::file::toUint8(file);
  auto deleter = [&](ofbx::IScene* ptr) { ptr->destroy(); };
  std::unique_ptr<ofbx::IScene, decltype(deleter)> scene(
      ofbx::load(fileContent.data(), fileContent.size(), true), deleter);

  LOG_D("Mesh count {}, ObjectCount {}", scene->getMeshCount(), scene->getAllObjectCount());

  for (int i = 0; i < scene->getMeshCount(); i++)
  {
    if (!parseMesh(scene.get(), i))
    {
    }
  }

  /*
  for (auto i = 0U; i < scene->mNumMaterials; i++)
  {
    if (!parseMaterial(scene, i, path))
      return false;
  }

  // Parse scene nodes
  std::stack<aiNode*> searchStack;
  searchStack.push(scene->mRootNode);

  Mat4 transform{1.f};

  while (!searchStack.empty())
  {
    auto node = searchStack.top();
    searchStack.pop();

    auto nodeTransform = aiMatrix4x4ToGlm(node->mTransformation);
    transform = nodeTransform * transform;

    LOG_D("Node: {}, transform {}", node->mName.C_Str(), glm::to_string(nodeTransform));
  }

  for (auto i = 0U; i < scene->mNumMeshes; i++)
  {
    if (!parseMesh(scene, i))
      return false;
  }

  mStaticMesh->materials(std::move(mMaterials));
  */
  mStaticMesh->positions(std::move(mPositions));
  mStaticMesh->normals(std::move(mNormals));
  mStaticMesh->uvChannels(std::move(mUVChannels));
  mStaticMesh->indices(std::move(mIndices));
  mStaticMesh->subMeshes(std::move(mSubMeshes));

  mStaticMesh->update();

  return true;
}

bool OFBXLoader::parseMesh(ofbx::IScene* scene, int meshIndex)
{
  assert(meshIndex < scene->getMeshCount());

  const auto* mesh = scene->getMesh(meshIndex);
  const auto* geometry = mesh->getGeometry();

  LOG_D("Mesh name: {}", mesh->name);

  LOG_D("Vertex count {} index count {}", geometry->getVertexCount(), geometry->getIndexCount());

  const auto vertexOffset = mPositions.size();
  LOG_D("Vertex offset: {}", vertexOffset);

  assert(geometry->getNormals());
  assert(geometry->getVertexCount() == geometry->getIndexCount());

  //
  // TODO we can first iterate over meshes and do one reserve, to avoid potential very large
  // reallocs
  mPositions.reserve(vertexOffset + geometry->getVertexCount());
  mNormals.reserve(vertexOffset + geometry->getVertexCount());

  for (int i = 0; i < geometry->getVertexCount(); i++)
  {
    auto* v = geometry->getVertices() + i;
    mPositions.push_back(Vec3{v->x, v->y, v->z});
    auto* n = geometry->getNormals() + i;
    mNormals.push_back(Vec3{n->x, n->y, n->z});
  }

  for (int uvChannel = 0; geometry->getUVs(uvChannel); uvChannel++)
  {
    if (mUVChannels.size() <= static_cast<size_t>(uvChannel))
    {
      mUVChannels.push_back({});
    }
    mUVChannels[uvChannel].resize(geometry->getVertexCount());

    auto channel = geometry->getUVs(uvChannel);
    for (int i = 0; i < geometry->getVertexCount(); i++)
    {
      mUVChannels[uvChannel][i] = {channel[i].x, channel[i].y};
    }
  }

  mSubMeshes.push_back({static_cast<uint32>(mIndices.size() * sizeof(uint32)),
                        static_cast<uint32>(geometry->getIndexCount()), 0});
  for (int i = 0; i < geometry->getIndexCount(); i++)
  {
    LOG_D("Face index: {}", geometry->getFaceIndices()[i]);
    int fbxIndex = geometry->getFaceIndices()[i];
    auto index = fbxIndex >= 0 ? fbxIndex : (-fbxIndex) - 1;
    mIndices.emplace_back(vertexOffset + static_cast<uint32>(index));
  }

  return true;
}

} // namespace aw::engine
