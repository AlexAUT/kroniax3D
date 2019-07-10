#include <aw/graphics/core/transform.hpp>

#include <glm/gtc/matrix_transform.hpp>

namespace aw
{
const Mat4& Transform::toMatrix() const
{
  if (mIsCacheDirty)
  {
    mTransform = Mat4(1.f);
    Mat4 scaling = glm::scale(mTransform, mScale);
    Mat4 rotation = glm::mat4_cast(mRotation);
    Mat4 translation = glm::translate(mTransform, mPosition);
    mTransform = translation * rotation * scaling;

    mIsCacheDirty = false;
  }

  return mTransform;
}
} // namespace aw
