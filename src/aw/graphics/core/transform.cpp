#include <aw/graphics/core/transform.hpp>

#include <glm/gtc/matrix_transform.hpp>

namespace aw::graphics
{
const math::Mat4& Transform::toMatrix() const
{
  if (mIsCacheDirty)
  {
    mTransform = math::Mat4(1.f);
    math::Mat4 scaling = glm::scale(mTransform, mScale);
    math::Mat4 rotation = glm::mat4_cast(mRotation);
    math::Mat4 translation = glm::translate(mTransform, mPosition);
    mTransform = translation * rotation * scaling;

    mIsCacheDirty = false;
  }

  return mTransform;
}
} // namespace aw::graphics
