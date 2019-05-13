#include <aw/util/color.hpp>

namespace aw
{
Color tintColor(Color c, float amount)
{
  return {c.r - c.r * amount, c.g - c.g * amount, c.b - c.b * amount};
}

Color shadeColor(Color c, float amount)
{
  return {c.r + (1.f - c.r) * amount, c.g + (1.f - c.g) * amount, c.b + (1.f - c.b) * amount};
}
} // namespace aw
