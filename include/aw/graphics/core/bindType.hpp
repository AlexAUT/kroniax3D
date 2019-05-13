#pragma once

namespace aw::gpu
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
