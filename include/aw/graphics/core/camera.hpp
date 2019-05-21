#pragma once

#include <aw/util/math/constants.hpp>
#include <aw/util/math/matrix.hpp>
#include <aw/util/math/quat.hpp>
#include <aw/util/math/vector.hpp>

namespace aw::graphics
{
class Camera
{
public:
  void orthographic(bool value);
  bool orthographic() const;

  void aspectRatio(float ratio);
  float aspectRatio() const;

  void orthoWidth(float width);
  float orthoWidth() const;

  void fieldOfView(float fov);
  float fieldOfView() const;

  void nearClipPlane(float near);
  float nearClipPlane() const;

  void farClipPlane(float far);
  float farClipPlane() const;

  void position(math::Vec3 position);
  math::Vec3 position() const;

  void rotation(math::Quat rotation);
  math::Quat rotation() const;

  const math::Mat4& inverseView() const;
  const math::Mat4& view() const;
  const math::Mat4& projection() const;
  const math::Mat4& viewProjection() const;

private:
  // Lazy updates
  void updateViewMatrix() const;
  void updateProjectionMatrix() const;
  void updateViewProjectionMatrix() const;

private:
  bool mIsOrthographic{false};

  float mAspectRatio{16.f / 9.f};
  float mOrthoWidth{1920.f};
  float mFieldOfView{90 * math::to_rad()};

  float mNear{0.1f};
  float mFar{1000.f};

  math::Vec3 mPosition{0.f};
  math::Quat mRotation{0.f, 0.f, 0.f, 1.f};

  mutable bool mViewDirty{true};
  mutable bool mProjectionDirty{true};
  mutable math::Mat4 mInverseViewMatrix;
  mutable math::Mat4 mViewMatrix;
  mutable math::Mat4 mProjectionMatrix;
  mutable math::Mat4 mViewProjectionMatrix;
};
} // namespace aw::graphics
