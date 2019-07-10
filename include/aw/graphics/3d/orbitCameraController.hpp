#pragma once

#include <aw/util/math/vector.hpp>

namespace aw
{
class Camera;

class OrbitCameraController
{
public:
  void lookAt(Vec3 lookAt);
  Vec3 lookAt() const;

  void distance(float distance);
  float distance() const;

  void rotation(Vec2 rotation);
  Vec2 rotation() const;

  void apply(Camera& camera);

private:
  void update();

private:
  Vec3 mLookAt{0.f, 0.f, 0.f};
  float mDistance{1.f};

  Vec2 mRotation{0.f};
};
} // namespace aw
