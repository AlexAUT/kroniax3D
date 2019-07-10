#pragma once

#include <aw/graphics/core/pixelFormat.hpp>
#include <aw/opengl/types.hpp>
#include <aw/util/math/vector.hpp>

namespace aw
{
class Image;

class Texture2D
{
public:
  enum class MinFilter
  {
    NEAREST,
    LINEAR,
    NEAREST_MIPMAP_NEAREST,
    NEAREST_MIPMAP_LINEAR,
    LINEAR_MIPMAP_LINEAR,
  };
  enum class MagFilter
  {
    NEAREST,
    LINEAR,
  };
  enum class WrapMode
  {
    CLAMP_TO_EDGE,
    CLAMP_TO_BORDER,
    MIRRORED_REPEAT,
    REPEAT,
  };
  Texture2D();
  ~Texture2D();

  void load(const Image& img);
  void load(const void* data, unsigned width, unsigned height, PixelFormat pixelFormat);
  void loadCompressed(const void* data, PixelFormat format);

  void bind(unsigned textureUnit = 0) const;
  void unbind() const;

  void minFilter(MinFilter type);
  void magFilter(MagFilter type);
  void wrapMode(WrapMode mode);
  void wrapModeS(WrapMode mode);
  void wrapModeT(WrapMode mode);

  GLuint id() const { return mId; }
  Vec2u size() const { return mSize; }
  PixelFormat pixelFormat() const { return mPixelFormat; }

private:
private:
  GLuint mId;

  Vec2u mSize;
  PixelFormat mPixelFormat;

  // Used to unbind the correct texture unit
  mutable unsigned mBoundTextureUnit;
};

} // namespace aw
