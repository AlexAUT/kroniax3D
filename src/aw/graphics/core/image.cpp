#include <aw/graphics/core/image.hpp>

#include <aw/graphics/log.hpp>
#include <aw/util/file/converters.hpp>
#include <aw/util/file/inputStream.hpp>

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.hpp"

#include <cstring>

namespace aw::graphics
{
Image::Image(PixelFormat format, unsigned width, unsigned height, std::unique_ptr<uint8> data) :
    mData(std::move(data)),
    mWidth(width),
    mHeight(height),
    mPixelFormat(format)
{
  resizeInternalPtr();
}

bool Image::loadFromPath(std::string_view path)
{
  file::InputStream stream(path);
  if (!stream.isOpen())
  {
    LOG_GRAPHICS_E("Failed to open path: {}", path);
    return false;
  }
  std::vector<uint8> fileBuffer = file::toUint8(stream);
  int w, h, channelCount;
  uint8* ptr = stbi_load_from_memory(fileBuffer.data(), fileBuffer.size(), &w, &h, &channelCount,
                                     STBI_default);

  if (ptr)
  {
    mWidth = w;
    mHeight = h;

    // Set pixel format
    switch (channelCount)
    {
    case 1:
      mPixelFormat = PixelFormat::R8;
      break;
    case 2:
      mPixelFormat = PixelFormat::RG8;
      break;
    case 3:
      mPixelFormat = PixelFormat::RGB8;
      break;
    case 4:
      mPixelFormat = PixelFormat::RGBA8;
      break;
    }

    resizeInternalPtr();
    if (!mData)
    {
      stbi_image_free(ptr);
      return false;
    }
    size_t size = pixelFormatToImageSize(mPixelFormat, mWidth, mHeight);
    std::memcpy(mData.get(), ptr, size);
    stbi_image_free(ptr);

    return true;
  }
  else
    LOG_GRAPHICS_E("Failed to load image: {}", path);

  return false;
}

void Image::resize(unsigned width, unsigned height)
{
  mWidth = width;
  mHeight = height;
  resizeInternalPtr();
}

void Image::pixelFormat(PixelFormat pixelFormat)
{
  mPixelFormat = pixelFormat;
  resizeInternalPtr();
}

void Image::resizeInternalPtr()
{
  size_t size = pixelFormatToImageSize(mPixelFormat, mWidth, mHeight);
  uint8* newBuffer = static_cast<uint8*>(realloc(mData.get(), size));
  mData.release();
  if (newBuffer)
    mData.reset(newBuffer);
}

Image Image::convertToPixelFormat(const Image& image, PixelFormat newFormat)
{
  Image newImage;
  newImage.mHeight = image.mHeight;
  newImage.mWidth = image.mWidth;
  newImage.mPixelFormat = newFormat;
  newImage.resizeInternalPtr();

  const auto numPixels = image.mWidth * image.mHeight;

  if (newFormat == PixelFormat::RGBFloat)
  {
    if (image.pixelFormat() == PixelFormat::RGB8)
    {
      const uint8* oldImageIter = reinterpret_cast<const uint8*>(image.mData.get());
      float* newImageIter = reinterpret_cast<float*>(newImage.mData.get());

      for (unsigned i = 0u; i < numPixels * 3; i++)
      {
        *newImageIter = static_cast<float>(*oldImageIter) / 255.f;
        newImageIter++;
        oldImageIter++;
      }
    }
    else
    {
      assert(false && "Conversion not supported yet");
    }
  }
  else if (newFormat == PixelFormat::RGBAFloat)
  {
    if (image.pixelFormat() == PixelFormat::RGB8)
    {
      const uint8* oldImageIter = reinterpret_cast<const uint8*>(image.mData.get());
      float* newImageIter = reinterpret_cast<float*>(newImage.mData.get());

      int counter = 0;
      for (unsigned i = 0u; i < numPixels * 4; i++)
      {
        if (++counter == 4)
        {
          counter = 0;
          *newImageIter = 1.f;
        }
        else
        {
          *newImageIter = static_cast<float>(*oldImageIter) / 255.f;
          oldImageIter++;
        }
        newImageIter++;
      }
    }
    else if (image.pixelFormat() == PixelFormat::RGBA8)
    {
      const uint8* oldImageIter = reinterpret_cast<const uint8*>(image.mData.get());
      float* newImageIter = reinterpret_cast<float*>(newImage.mData.get());

      for (unsigned i = 0u; i < numPixels * 4; i++)
      {
        *newImageIter = static_cast<float>(*oldImageIter) / 255.f;
        newImageIter++;
        oldImageIter++;
      }
    }
    else
    {
      assert(false && "Conversion not supported yet");
    }
  }
  else
  {
    assert(false && "Conversion not supported yet");
  }

  return newImage;
}

} // namespace aw::graphics
