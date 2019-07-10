#include <aw/graphics/3d/orbitCameraController.hpp>

#include <aw/graphics/core/camera.hpp>
#include <aw/graphics/log.hpp>

#include <glm/trigonometric.hpp>

namespace aw
{
void OrbitCameraController::lookAt(Vec3 lookAt)
{
  mLookAt = lookAt;
}

Vec3 OrbitCameraController::lookAt() const
{
  return mLookAt;
}

void OrbitCameraController::distance(float distance)
{
  mDistance = distance;
}

float OrbitCameraController::distance() const
{
  return mDistance;
}

void OrbitCameraController::rotation(Vec2 rotation)
{
  mRotation = rotation;
}

Vec2 OrbitCameraController::rotation() const
{
  return mRotation;
}

void OrbitCameraController::apply(Camera& camera)
{
  using std::cos;
  using std::sin;

  Vec3 offsetDir{sin(mRotation.y) * cos(mRotation.x), sin(mRotation.x),
                 cos(mRotation.y) * cos(mRotation.x)};
  auto position = mLookAt + offsetDir * mDistance;

  Vec3 rotation{-mRotation.x, mRotation.y, 0.f};

  camera.position(position);
  camera.rotation(Quat(rotation));
}
} // namespace aw
