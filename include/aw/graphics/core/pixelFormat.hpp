#pragma once

#include <cmath>

namespace aw
{
enum class PixelFormat
{
  // uint8's
  R8,
  RG8,
  RGB8,
  RGBA8,
  // Floats
  RFloat,
  RGFloat,
  RGBFloat,
  RGBAFloat,
  // ETC2
  RGB_ETC2,
  RGBA1_ETC2,
  RGBA_ETC2,
  // Depth
  Depth16,
  Depth24,
  DepthFloat,
  // Depth/Stencil
  Depth24Stencil8,
  DepthFloatStencil8
};

inline constexpr unsigned pixelFormatToChannelCount(PixelFormat format);
inline constexpr unsigned pixelFormatToImageSize(PixelFormat format, int w, int h);
inline constexpr bool isPixelFormatCompressed(PixelFormat format);

inline constexpr unsigned pixelFormatToChannelCount(PixelFormat format)
{
  switch (format)
  {
  // uint8's
  case PixelFormat::R8:
    return 1;
  case PixelFormat::RG8:
    return 2;
  case PixelFormat::RGB8:
    return 3;
  case PixelFormat::RGBA8:
    return 4;
  // floats
  case PixelFormat::RFloat:
    return 1;
  case PixelFormat::RGFloat:
    return 2;
  case PixelFormat::RGBFloat:
    return 3;
  case PixelFormat::RGBAFloat:
    return 4;
  // ETC2
  case PixelFormat::RGB_ETC2:
    return 3;
  case PixelFormat::RGBA1_ETC2:
    return 4;
  case PixelFormat::RGBA_ETC2:
    return 4;
  // Depth
  case PixelFormat::Depth16:
    [[fallthrough]];
  case PixelFormat::Depth24:
    [[fallthrough]];
  case PixelFormat::DepthFloat:
    return 1;
  // Depth Stencil
  case PixelFormat::Depth24Stencil8:
    [[fallthrough]];
  case PixelFormat::DepthFloatStencil8:
    return 2;
  }

  return 0;
}

inline constexpr unsigned pixelFormatToImageSize(PixelFormat format, int w, int h)
{
  auto numChannels = pixelFormatToChannelCount(format);
  switch (format)
  {
  // uint8's
  case PixelFormat::R8:
  case PixelFormat::RG8:
  case PixelFormat::RGB8:
  case PixelFormat::RGBA8:
    return w * h * numChannels;
  // floats
  case PixelFormat::RFloat:
  case PixelFormat::RGFloat:
  case PixelFormat::RGBFloat:
  case PixelFormat::RGBAFloat:
    return w * h * numChannels * sizeof(float);
  // ETC2
  case PixelFormat::RGB_ETC2:
    return std::ceil(w / 4) * std::ceil(h / 4) * 8;
  case PixelFormat::RGBA_ETC2:
    return std::ceil(w / 4) * std::ceil(h / 4) * 8;
  case PixelFormat::RGBA1_ETC2:
    return std::ceil(w / 4) * std::ceil(h / 4) * 16;
  // Depth
  case PixelFormat::Depth16:
    return w * h * 2;
  case PixelFormat::Depth24:
    return w * h * 3;
  case PixelFormat::DepthFloat:
    return w * h * sizeof(float);
  // Depth Stencil
  case PixelFormat::Depth24Stencil8:
    return w * h * 4;
  case PixelFormat::DepthFloatStencil8:
    return w * h * (sizeof(float) + 1);
  }

  return 0;
}

inline constexpr bool isPixelFormatCompressed(PixelFormat format)
{
  switch (format)
  {
  case PixelFormat::RGB_ETC2:
    [[fallthrough]];
  case PixelFormat::RGBA_ETC2:
    [[fallthrough]];
  case PixelFormat::RGBA1_ETC2:
    return true;
  default:
    return false;
  }
}
} // namespace aw
