#pragma once

namespace aw
{
struct Color
{
public:
  float r, g, b, a;

  template <class Archive>
  void serialize(Archive& archive);
};

Color tintColor(Color color, float amount);
Color shadeColor(Color color, float amount);
} // namespace aw

