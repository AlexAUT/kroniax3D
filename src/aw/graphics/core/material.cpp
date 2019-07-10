#include <aw/graphics/core/material.hpp>

#include <aw/graphics/core/shaderProgram.hpp>
#include <aw/opengl/opengl.hpp>

namespace aw
{
Texture2D* getFallbackTexture()
{
  auto init = []() {
    Texture2D* tex = new Texture2D();
    uint8 color[] = {255, 20, 147};
    tex->bind();
    tex->load(&color, 1, 1, PixelFormat::RGB8);
    tex->unbind();
    return tex;
  };
  static Texture2D* tex = init();
  return tex;
}

void Material::assignToShader(const Material& material, const ShaderProgram& shader,
                              const char* uniformName)
{
  shader.bind();

  shader.set("diffuseColor", material.diffuseColor());
  shader.set("ambientColor", material.ambientColor());
  shader.set("specularColor", material.specularColor());
  shader.set("enableDiffuseTex", material.diffuseSlotsCount() > 0);

  if (material.diffuseSlotsCount() > 0)
  {
    auto* tex = material.diffuseSlot(0).texture2D.get();
    if (!tex)
      tex = getFallbackTexture();
    tex->bind();
  }
  shader.set("enableDecalTex", material.diffuseSlotsCount() > 1);
  if (material.diffuseSlotsCount() > 1)
  {
    auto* tex = material.diffuseSlot(1).texture2D.get();
    if (!tex)
      tex = getFallbackTexture();
    tex->bind(1);
  }
}

Material::Material(std::string name) : mName(name) {}

void Material::ambientColor(Color color)
{
  mAmbientColor = color;
}

std::string_view Material::name() const
{
  return mName;
}

Color Material::ambientColor() const
{
  return mAmbientColor;
}

void Material::diffuseColor(Color color)
{
  mDiffuseColor = color;
}

Color Material::diffuseColor() const
{
  return mDiffuseColor;
}

void Material::specularColor(Color color)
{
  mSpecularColor = color;
}

Color Material::specularColor() const
{
  return mSpecularColor;
}

void Material::addDiffuseTexture(const TextureSlot& textureSlot)
{
  mDiffuseSlots.push_back(textureSlot);
}

void Material::addNormalTexture(const TextureSlot& textureSlot)
{
  mNormalSlots.push_back(textureSlot);
}

size_t Material::diffuseSlotsCount() const
{
  return mDiffuseSlots.size();
}

const TextureSlot& Material::diffuseSlot(unsigned index) const
{
  return mDiffuseSlots[index];
}

} // namespace aw
