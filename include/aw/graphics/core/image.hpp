#pragma once

#include <aw/graphics/core/pixelFormat.hpp>
#include <aw/util/types.hpp>

#include <istream>
#include <memory>
#include <string_view>

namespace aw
{
class Image
{
public:
  static Image convertToPixelFormat(const Image& image, PixelFormat newFormat);

public:
  Image() = default;
  Image(PixelFormat format, unsigned width, unsigned height, std::unique_ptr<uint8> data = nullptr);

  bool loadFromPath(std::string_view path);

  // This does invalidate the content of the image
  void resize(unsigned width, unsigned height);
  // This does invalidate the content of the image
  void pixelFormat(PixelFormat pixelFormat);

  unsigned width() const { return mWidth; }
  unsigned height() const { return mHeight; }
  unsigned channelCount() const { return pixelFormatToChannelCount(mPixelFormat); }

  // The default interpretation is row wise
  uint8* pixels() { return mData.get(); }
  const uint8* pixels() const { return mData.get(); }

  size_t pixelSize() const { return pixelFormatToImageSize(mPixelFormat, mWidth, mHeight); }

  PixelFormat pixelFormat() const { return mPixelFormat; }

private:
  void resizeInternalPtr();

private:
  std::unique_ptr<uint8> mData;
  unsigned mWidth;
  unsigned mHeight;
  PixelFormat mPixelFormat;
};

} // namespace aw
