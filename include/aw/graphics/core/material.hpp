#pragma once

#include <aw/graphics/core/texture2D.hpp>
#include <aw/util/color.hpp>
#include <aw/util/math/vector.hpp>
#include <aw/util/types.hpp>

#include <memory>
#include <string>
#include <vector>

namespace aw
{
class ShaderProgram;

struct TextureSlot
{
  std::string texName;
  std::shared_ptr<Texture2D> texture2D;
  unsigned uvIndex;
  Texture2D::MinFilter minFilter;
  Texture2D::MagFilter magFilter;
  Texture2D::WrapMode modeS;
  Texture2D::WrapMode modeT;
};

class Material
{
public:
  // TODO: Refactor, this does not belong here...
  static void assignToShader(const Material& material, const ShaderProgram& shader,
                             const char* uniformName);

public:
  explicit Material(std::string name);

  std::string_view name() const;

  void addDiffuseTexture(const TextureSlot& textureSlot);
  void addNormalTexture(const TextureSlot& textureSlot);

  void ambientColor(Color color);
  Color ambientColor() const;

  void diffuseColor(Color color);
  Color diffuseColor() const;

  void specularColor(Color color);
  Color specularColor() const;

  size_t diffuseSlotsCount() const;
  const TextureSlot& diffuseSlot(unsigned index) const;

private:
private:
  std::string mName;

  Color mAmbientColor{0.f, 0.f, 0.f, 1.f};
  Color mDiffuseColor{0.f, 0.f, 0.f, 1.f};
  Color mSpecularColor{0.f, 0.f, 0.f, 1.f};

  std::vector<TextureSlot> mDiffuseSlots;
  std::vector<TextureSlot> mNormalSlots;
};
} // namespace aw
