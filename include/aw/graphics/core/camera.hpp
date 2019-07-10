#pragma once

#include <aw/util/math/constants.hpp>
#include <aw/util/math/matrix.hpp>
#include <aw/util/math/quat.hpp>
#include <aw/util/math/vector.hpp>

namespace aw
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

  void position(Vec3 position);
  Vec3 position() const;

  void rotation(Quat rotation);
  Quat rotation() const;

  const Mat4& inverseView() const;
  const Mat4& view() const;
  const Mat4& projection() const;
  const Mat4& viewProjection() const;

private:
  // Lazy updates
  void updateViewMatrix() const;
  void updateProjectionMatrix() const;
  void updateViewProjectionMatrix() const;

private:
  bool mIsOrthographic{false};

  float mAspectRatio{16.f / 9.f};
  float mOrthoWidth{1920.f};
  float mFieldOfView{90 * to_rad()};

  float mNear{0.1f};
  float mFar{1000.f};

  Vec3 mPosition{0.f};
  Quat mRotation{glm::identity<Quat>()};

  mutable bool mViewDirty{true};
  mutable bool mProjectionDirty{true};
  mutable Mat4 mInverseViewMatrix;
  mutable Mat4 mViewMatrix;
  mutable Mat4 mProjectionMatrix;
  mutable Mat4 mViewProjectionMatrix;
};
} // namespace aw
