#include <aw/graphics/core/texture2D.hpp>

#include <aw/graphics/core/image.hpp>
#include <aw/graphics/log.hpp>
#include <aw/opengl/opengl.hpp>

namespace aw
{
struct TextureFormat
{
  GLenum internal;
  GLenum format;
  GLenum dataType;
};
TextureFormat pixelFormatToOpengl(PixelFormat format);

Texture2D::Texture2D()
{
  glGenTextures(1, &mId);
}

Texture2D::~Texture2D()
{
  glDeleteTextures(1, &mId);
}

void Texture2D::load(const Image& image)
{
  load(image.pixels(), image.width(), image.height(), image.pixelFormat());
}

void Texture2D::load(const void* data, unsigned width, unsigned height, PixelFormat pixelFormat)
{
  auto [internal, format, dataType] = pixelFormatToOpengl(pixelFormat);

  if (!isPixelFormatCompressed(pixelFormat))
  {
    GL_CHECK(glTexImage2D(GL_TEXTURE_2D, 0, internal, width, height, 0, format, dataType, data));
    LOG_GRAPHICS_D("NOT COMPRESSED");
  }
  else
  {
    LOG_GRAPHICS_D("COMPRESSED! {}", static_cast<int>(pixelFormat));
    auto imageSize = pixelFormatToImageSize(pixelFormat, width, height);
    GL_CHECK(glCompressedTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, imageSize, data));
  }

  minFilter(MinFilter::LINEAR);
  magFilter(MagFilter::LINEAR);
  wrapMode(WrapMode::REPEAT);
}

void Texture2D::minFilter(MinFilter type)
{
  GLenum glType;
  switch (type)
  {
  case MinFilter::LINEAR:
    glType = GL_LINEAR;
    break;
  case MinFilter::LINEAR_MIPMAP_LINEAR:
    glType = GL_LINEAR_MIPMAP_LINEAR;
    break;
  case MinFilter::NEAREST_MIPMAP_NEAREST:
    glType = GL_NEAREST_MIPMAP_NEAREST;
    break;
  case MinFilter::NEAREST_MIPMAP_LINEAR:
    glType = GL_NEAREST_MIPMAP_LINEAR;
    break;
  case MinFilter::NEAREST:
    glType = GL_NEAREST;
    break;
  default:
    glType = GL_NEAREST;
    break;
  }

  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, glType));
}

void Texture2D::magFilter(MagFilter type)
{
  GLenum glType;
  switch (type)
  {
  case MagFilter::LINEAR:
    glType = GL_LINEAR;
    break;
  case MagFilter::NEAREST:
    glType = GL_NEAREST;
    break;
  default:
    glType = GL_NEAREST;
    break;
  }
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, glType));
}

GLenum wrapModeToGLType(Texture2D::WrapMode mode)
{
  switch (mode)
  {
  case Texture2D::WrapMode::REPEAT:
    return GL_REPEAT;
  case Texture2D::WrapMode::CLAMP_TO_EDGE:
    return GL_CLAMP_TO_EDGE;
  case Texture2D::WrapMode::MIRRORED_REPEAT:
    return GL_MIRRORED_REPEAT;
  case Texture2D::WrapMode::CLAMP_TO_BORDER:
#ifdef GL_CLAMP_TO_BORDER
    return GL_CLAMP_TO_BORDER;
#else
    return GL_CLAMP_TO_EDGE;
#endif
  default:
    return GL_REPEAT;
  }
}

void Texture2D::wrapMode(WrapMode mode)
{
  wrapModeS(mode);
  wrapModeT(mode);
}

void Texture2D::wrapModeS(WrapMode mode)
{
  auto glType = wrapModeToGLType(mode);
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, glType));
}

void Texture2D::wrapModeT(WrapMode mode)
{
  auto glType = wrapModeToGLType(mode);
  GL_CHECK(glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, glType));
}

void Texture2D::bind(unsigned int textureUnit) const
{
  GL_CHECK(glActiveTexture(GL_TEXTURE0 + textureUnit));
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, mId));
  mBoundTextureUnit = textureUnit;
}

void Texture2D::unbind() const
{
  GL_CHECK(glActiveTexture(GL_TEXTURE0 + mBoundTextureUnit));
  GL_CHECK(glBindTexture(GL_TEXTURE_2D, 0));
}

TextureFormat pixelFormatToOpengl(PixelFormat format)
{
  switch (format)
  {
  // uint8's
  case PixelFormat::R8:
    return {GL_R8, GL_RED, GL_UNSIGNED_BYTE};
  case PixelFormat::RG8:
    return {GL_RG8, GL_RG, GL_UNSIGNED_BYTE};
  case PixelFormat::RGB8:
    return {GL_RGB8, GL_RGB, GL_UNSIGNED_BYTE};
  case PixelFormat::RGBA8:
    return {GL_RGBA8, GL_RGB, GL_UNSIGNED_BYTE};
  // float
  case PixelFormat::RFloat:
    return {GL_R32F, GL_RED, GL_FLOAT};
  case PixelFormat::RGFloat:
    return {GL_RG32F, GL_RG, GL_FLOAT};
  case PixelFormat::RGBFloat:
    return {GL_RGB32F, GL_RGB, GL_FLOAT};
  case PixelFormat::RGBAFloat:
    return {GL_RGBA32F, GL_RGBA, GL_FLOAT};
  // etc2
  case PixelFormat::RGB_ETC2:
    return {GL_COMPRESSED_RGB8_ETC2, GL_RGB, GL_UNSIGNED_BYTE};
  case PixelFormat::RGBA_ETC2:
    return {GL_COMPRESSED_RGBA8_ETC2_EAC, GL_RGBA, GL_UNSIGNED_BYTE};
  case PixelFormat::RGBA1_ETC2:
    return {GL_COMPRESSED_RGB8_PUNCHTHROUGH_ALPHA1_ETC2, GL_RGB, GL_UNSIGNED_BYTE};
  // Depth
  case PixelFormat::Depth16:
    return {GL_DEPTH_COMPONENT16, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE};
  case PixelFormat::Depth24:
    return {GL_DEPTH_COMPONENT24, GL_DEPTH_COMPONENT, GL_UNSIGNED_BYTE};
  case PixelFormat::DepthFloat:
    return {GL_DEPTH_COMPONENT32F, GL_DEPTH_COMPONENT, GL_FLOAT};
  // Depth stencil
  case PixelFormat::Depth24Stencil8:
    return {GL_DEPTH24_STENCIL8, GL_DEPTH_STENCIL, GL_UNSIGNED_BYTE};
  case PixelFormat::DepthFloatStencil8:
    return {GL_DEPTH32F_STENCIL8, GL_DEPTH_STENCIL, GL_UNSIGNED_BYTE};
  }
  return {GL_NONE, GL_NONE};
}
} // namespace aw
