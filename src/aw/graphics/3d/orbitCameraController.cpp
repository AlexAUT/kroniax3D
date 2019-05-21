#include <aw/graphics/3d/orbitCameraController.hpp>

#include <aw/graphics/core/camera.hpp>
#include <aw/graphics/log.hpp>

#include <glm/trigonometric.hpp>

namespace aw::graphics
{
void OrbitCameraController::lookAt(math::Vec3 lookAt)
{
  mLookAt = lookAt;
}

math::Vec3 OrbitCameraController::lookAt() const
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

void OrbitCameraController::rotation(math::Vec2 rotation)
{
  mRotation = rotation;
}

math::Vec2 OrbitCameraController::rotation() const
{
  return mRotation;
}

void OrbitCameraController::apply(Camera& camera)
{
  using std::cos;
  using std::sin;

  math::Vec3 offsetDir{sin(mRotation.y) * cos(mRotation.x), sin(mRotation.x),
                       cos(mRotation.y) * cos(mRotation.x)};
  auto position = mLookAt + offsetDir * mDistance;
  LOG_GRAPHICS_W("POS: {} {} {}", position.x, position.y, position.z);
  LOG_GRAPHICS_D("Angle: {} {}", mRotation.x * math::to_deg(), mRotation.y * math::to_deg());

  math::Vec3 rotation{-mRotation.x, mRotation.y, 0.f};

  camera.position(position);
  camera.rotation(math::Quat(rotation));
}
} // namespace aw::graphics
