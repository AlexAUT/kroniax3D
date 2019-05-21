#pragma once

#include <aw/util/math/vector.hpp>

namespace aw::graphics
{
class Camera;

class OrbitCameraController
{
public:
  void lookAt(math::Vec3 lookAt);
  math::Vec3 lookAt() const;

  void distance(float distance);
  float distance() const;

  void rotation(math::Vec2 rotation);
  math::Vec2 rotation() const;

  void apply(Camera& camera);

private:
  void update();

private:
  math::Vec3 mLookAt{0.f, 0.f, 0.f};
  float mDistance{1.f};

  math::Vec2 mRotation{0.f};
};
} // namespace aw::graphics
