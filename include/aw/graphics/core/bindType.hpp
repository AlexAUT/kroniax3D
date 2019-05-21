#pragma once

namespace aw::graphics
{
enum class BindType
{
  ArrayBuffer,
  CopyReadBuffer,
  CopyWriteBuffer,
  ElementArrayBuffer,
  PixelPackBuffer,
  PixelUnpackBuffer,
  TransformFeedbackBuffer,
  UniformBuffer
};
}
