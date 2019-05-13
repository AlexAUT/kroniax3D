#pragma once

namespace aw::gpu
{
enum class UsageType
{
  StreamDraw,
  StreamRead,
  StreamCopy,
  StaticDraw,
  StaticRead,
  StaticCopy,
  DynamicDraw,
  DynamicRead,
  DynamicCopy,
};

}
