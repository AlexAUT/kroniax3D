#include <aw/engine/resources/loaders/assimpLoader.hpp>

#include <aw/engine/resources/staticMesh.hpp>
#include <aw/graphics/core/image.hpp>
#include <aw/graphics/core/texture2D.hpp>
#include <aw/util/file/converters.hpp>
#include <aw/util/file/inputStream.hpp>
#include <aw/util/file/path.hpp>
#include <aw/util/log/log.hpp>
#include <aw/util/math/vector.hpp>

#include <assimp/Importer.hpp>
#include <assimp/material.h>
#include <assimp/postprocess.h>
#include <assimp/scene.h>

#include <stack>

#include <glm/gtx/string_cast.hpp>

inline aw::Mat4 aiMatrix4x4ToGlm(const aiMatrix4x4& from)
{
  aw::Mat4 to;

  to[0][0] = static_cast<float>(from.a1);
  to[0][1] = static_cast<float>(from.b1);
  to[0][2] = static_cast<float>(from.c1);
  to[0][3] = static_cast<float>(from.d1);
  to[1][0] = static_cast<float>(from.a2);
  to[1][1] = static_cast<float>(from.b2);
  to[1][2] = static_cast<float>(from.c2);
  to[1][3] = static_cast<float>(from.d2);
  to[2][0] = static_cast<float>(from.a3);
  to[2][1] = static_cast<float>(from.b3);
  to[2][2] = static_cast<float>(from.c3);
  to[2][3] = static_cast<float>(from.d3);
  to[3][0] = static_cast<float>(from.a4);
  to[3][1] = static_cast<float>(from.b4);
  to[3][2] = static_cast<float>(from.c4);
  to[3][3] = static_cast<float>(from.d4);

  return to;
}

namespace aw::log
{
inline Module assimpLogModule("AssimpLoader");
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
int configToImporterFlags(AssimpLoader::Config config);

AssimpLoader::AssimpLoader(Config config) : mConfig(config) {}

bool AssimpLoader::load(StaticMesh& mesh, const char* path)
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

  Assimp::Importer importer;

  // Extension is last element, so we can directly supply the stringview
  auto extensionV = filePath::extension(file.getPath());

  auto fileContent = aw::file::toUint8(file);
  importer.ReadFileFromMemory(fileContent.data(), fileContent.size(),
                              configToImporterFlags(mConfig), extensionV.data());

  const auto* scene = importer.GetScene();

  LOG_D("Num meshes: {}\n", scene->mNumMeshes);

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
  mStaticMesh->positions(std::move(mPositions));
  mStaticMesh->normals(std::move(mNormals));
  mStaticMesh->uvChannels(std::move(mUVChannels));
  mStaticMesh->indices(std::move(mIndices));
  mStaticMesh->subMeshes(std::move(mSubMeshes));

  mStaticMesh->update();
  return true;
}

bool AssimpLoader::parseMesh(const aiScene* scene, unsigned meshIndex)
{
  assert(meshIndex < scene->mNumMeshes);

  const auto* mesh = scene->mMeshes[meshIndex];
  assert(mesh->HasPositions());
  assert(mesh->HasNormals());
  assert(mesh->HasFaces());

  LOG_D("Mesh name: {}", mesh->mName.C_Str());

  const auto vertexOffset = mPositions.size();
  LOG_D("Vertex offset: {}", vertexOffset);
  // TODO we can first iterate over meshes and do one reserve, to avoid potential very large
  // reallocs
  mPositions.reserve(vertexOffset + mesh->mNumVertices);
  mNormals.reserve(vertexOffset + mesh->mNumVertices);

  for (auto i = 0U; i < mesh->mNumVertices; i++)
  {
    mPositions.push_back(Vec3{mesh->mVertices[i].x, mesh->mVertices[i].y, mesh->mVertices[i].z});
    mNormals.push_back(Vec3{mesh->mNormals[i].x, mesh->mNormals[i].y, mesh->mNormals[i].z});
  }

  // First check if we have enough UVs created, if not create a new channel and resize it to
  // (previous subMeshes do not use this channel so we can set it to garbage)
  const auto uvChannelCount = mesh->GetNumUVChannels();
  while (mUVChannels.size() <= uvChannelCount)
  {
    mUVChannels.emplace_back();
    if (mUVChannels.size() != 1)
      mUVChannels.back().resize(mUVChannels.front().size());
  }

  for (auto i = 0U; i < uvChannelCount; i++)
  {
    mUVChannels[i].reserve(mUVChannels[i].size() + mesh->mNumVertices);
    for (auto v = 0U; v < mesh->mNumVertices; v++)
    {
      mUVChannels[i].emplace_back(mesh->mTextureCoords[i][v].x, mesh->mTextureCoords[i][v].y);
    }
  }

  mSubMeshes.push_back({static_cast<uint32>(mIndices.size() * sizeof(uint32)), mesh->mNumFaces * 3,
                        mesh->mMaterialIndex});
  // mIndices.reserve(mIndices.size() + (3 * mesh->mNumFaces));

  for (auto i = 0U; i < mesh->mNumFaces; i++)
  {
    const auto& face = mesh->mFaces[i];
    assert(face.mNumIndices == 3);
    mIndices.emplace_back(vertexOffset + face.mIndices[0]);
    mIndices.emplace_back(vertexOffset + face.mIndices[1]);
    mIndices.emplace_back(vertexOffset + face.mIndices[2]);
  }

  return true;
}

aw::Texture2D::WrapMode assimpWrapModeToAw(aiTextureMapMode mode)
{
  using WrapMode = aw::Texture2D::WrapMode;
  switch (mode)
  {
  case aiTextureMapMode_Wrap:
    return WrapMode::REPEAT;
  case aiTextureMapMode_Mirror:
    return WrapMode::MIRRORED_REPEAT;
  case aiTextureMapMode_Decal:
    return WrapMode::CLAMP_TO_BORDER;
  case aiTextureMapMode_Clamp:
    return WrapMode::CLAMP_TO_EDGE;
  default:
    return WrapMode::REPEAT;
  }
}

std::string searchTexture(std::string_view texName, std::string_view texPath,
                          std::string_view meshFilePath)
{
  // Try path directly
  {
    file::InputStream file(texPath);
    if (file.isOpen())
      return std::string(texPath);
  }
  // TODO implement more search paths
  LOG_D("PATHS: \n{}\n{}\n{}", texName, texPath, meshFilePath);
  return "";
}

bool AssimpLoader::parseMaterial(const aiScene* scene, unsigned matIndex, const char* path)
{
  LOG_D("IN MATERIAL!");
  assert(matIndex < scene->mNumMaterials);
  const auto assimpMat = scene->mMaterials[matIndex];

  aiString matName;
  if (assimpMat->Get(AI_MATKEY_NAME, matName) != AI_SUCCESS)
    LOG_W("Material without name found!");
  mMaterials.emplace_back(matName.C_Str());
  auto& mat = mMaterials.back();

  LOG_D("Mat name: {}", mat.name());

  aiColor3D color;
  if (assimpMat->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS)
  {
    mat.diffuseColor({color.r, color.g, color.b, 1.f});
  }
  if (assimpMat->Get(AI_MATKEY_COLOR_AMBIENT, color) == AI_SUCCESS)
  {
    mat.ambientColor({color.r, color.g, color.b, 1.f});
  }
  if (assimpMat->Get(AI_MATKEY_COLOR_SPECULAR, color) == AI_SUCCESS)
  {
    mat.specularColor({color.r, color.g, color.b, 1.f});
  }

  // Load diffuse textures
  unsigned diffuseCount = assimpMat->GetTextureCount(aiTextureType_DIFFUSE);
  LOG_D("DIFFUSE COUNT: {}", diffuseCount);
  for (unsigned i = 0; i < diffuseCount; i++)
  {
    aiString aPath;
    aiTextureMapping mapping = aiTextureMapping_UV;
    aiTextureOp op = aiTextureOp_Add;
    unsigned uvIndex;
    float blend;
    aiTextureMapMode mapMode;

    assimpMat->GetTexture(aiTextureType_DIFFUSE, i, &aPath, &mapping, &uvIndex, &blend, &op,
                          &mapMode);
    if (mapping != aiTextureMapping_UV)
    {
      LOG_E("Unsupported texture mapping mode, only UV mapping is supported!");
      return false;
    }
    aw::TextureSlot slot;
    slot.uvIndex = uvIndex;
    auto wrapMode = assimpWrapModeToAw(mapMode);
    slot.modeS = wrapMode;
    slot.modeT = wrapMode;
    slot.magFilter = aw::Texture2D::MagFilter::LINEAR;
    slot.minFilter = aw::Texture2D::MinFilter::LINEAR;

    std::string texPath(aPath.C_Str());
    auto posForwardSlash = texPath.find_last_of("/") + 1;
    auto posBackwardSlash = texPath.find_last_of("\\") + 1;
    auto pos = std::max(posForwardSlash, posBackwardSlash);

    auto texName = texPath.substr(pos);
    slot.texName = texName;

    std::string foundTexPath = searchTexture(texName, texPath, path);
    if (!foundTexPath.empty())
    {
      Image image;
      if (!image.loadFromPath(foundTexPath))
      {
        LOG_E("Failed to load texture: {}", foundTexPath);
        return false;
      }

      auto imageSize = image.pixelSize();
      LOG_W("Image {} {} {} {}", image.width(), image.height(),
            static_cast<int>(image.pixelFormat()), imageSize);

      slot.texture2D = std::make_shared<Texture2D>();
      slot.texture2D->bind();
      slot.texture2D->load(image);
      slot.texture2D->wrapModeS(slot.modeS);
      slot.texture2D->wrapModeT(slot.modeT);
      slot.texture2D->minFilter(slot.minFilter);
      slot.texture2D->magFilter(slot.magFilter);

      slot.texture2D->unbind();
    }
    else
      slot.texture2D = nullptr;

    mat.addDiffuseTexture(slot);
  }

  return true;
}

int configToImporterFlags(AssimpLoader::Config config)
{
  using T = AssimpLoader::Config::NormalType;
  return aiProcess_Triangulate | ((config.normals == T::Hard) ? aiProcess_GenNormals : 0) |
         ((config.normals == T::Smooth) ? aiProcess_GenSmoothNormals : 0);
}

} // namespace aw::engine
