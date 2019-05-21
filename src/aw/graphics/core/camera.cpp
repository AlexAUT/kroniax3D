#include <aw/graphics/core/camera.hpp>

#include <glm/gtc/matrix_access.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/quaternion.hpp>

namespace aw::graphics
{

void Camera::orthographic(bool value)
{
  if (mIsOrthographic != value)
  {
    mIsOrthographic = value;
    mProjectionDirty = true;
  }
}

bool Camera::orthographic() const
{
  return mIsOrthographic;
}

void Camera::aspectRatio(float ratio)
{
  if (mAspectRatio != ratio)
  {
    mAspectRatio = ratio;
    mProjectionDirty = true;
  }
}

float Camera::aspectRatio() const
{
  return mAspectRatio;
}

void Camera::orthoWidth(float width)
{
  if (mOrthoWidth != width)
  {
    mOrthoWidth = width;
    mProjectionDirty = true;
  }
}

float Camera::orthoWidth() const
{
  return mOrthoWidth;
}

void Camera::fieldOfView(float fov)
{
  if (mFieldOfView != fov)
  {
    mFieldOfView = fov;
    mProjectionDirty = fov;
  }
}

float Camera::fieldOfView() const
{
  return mFieldOfView;
}

void Camera::nearClipPlane(float near)
{
  if (mNear != near)
  {
    mNear = near;
    mProjectionDirty = true;
  }
}

float Camera::nearClipPlane() const
{
  return mNear;
}

void Camera::farClipPlane(float far)
{
  if (mFar != far)
  {
    mFar = far;
    mProjectionDirty = true;
  }
}

float Camera::farClipPlane() const
{
  return mFar;
}

void Camera::position(math::Vec3 position)
{
  if (mPosition != position)
  {
    mPosition = position;
    mViewDirty = true;
  }
}

math::Vec3 Camera::position() const
{
  return mPosition;
}

void Camera::roatation(math::Quat rotation)
{
  if (mRotation != rotation)
  {
    mRotation = rotation;
    mViewDirty = true;
  }
}

math::Quat Camera::rotation() const
{
  return mRotation;
}

const math::Mat4& Camera::inverseView() const
{
  if (mViewDirty)
    updateViewMatrix();
  return mInverseViewMatrix;
}

const math::Mat4& Camera::view() const
{
  if (mViewDirty)
    updateViewMatrix();
  return mViewMatrix;
}

const math::Mat4& Camera::projection() const
{
  if (mProjectionDirty)
    updateProjectionMatrix();
  return mProjectionMatrix;
}

const math::Mat4& Camera::viewProjection() const
{
  updateViewProjectionMatrix();
  return mViewProjectionMatrix;
}

void Camera::updateViewMatrix() const
{
  mViewDirty = false;

  auto rotationMatrix = glm::mat4_cast(mRotation);
  mInverseViewMatrix = glm::translate(math::Mat4(1.f), mPosition) * rotationMatrix;
  mViewMatrix = glm::inverse(mInverseViewMatrix);
}

void Camera::updateProjectionMatrix() const
{
  mProjectionDirty = false;
  if (mIsOrthographic)
  {
    const float widthHalf = mOrthoWidth / 2.f;
    const float heightHalf = widthHalf / mAspectRatio;
    mProjectionMatrix = glm::ortho(-widthHalf, widthHalf, -heightHalf, heightHalf, mNear, mFar);
  }
  else
  {
    mProjectionMatrix = glm::perspective(mFieldOfView, mAspectRatio, mNear, mFar);
  }
}

void Camera::updateViewProjectionMatrix() const
{
  updateViewMatrix();
  updateProjectionMatrix();

  mViewProjectionMatrix = mProjectionMatrix * mViewMatrix;
}

} // namespace aw::graphics
