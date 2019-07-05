#pragma once

#include <aw/util/math/matrix.hpp>
#include <aw/util/math/quat.hpp>
#include <aw/util/math/vector.hpp>

namespace aw::graphics
{
class Transform
{
public:
  void position(math::Vec3 pos);
  math::Vec3 position() const;

  void scale(math::Vec3 scale);
  math::Vec3 scale() const;

  void rotation(math::Quat rotation);
  math::Quat rotation() const;

  const math::Mat4& toMatrix() const;

private:
  void invalidateCache();

private:
  math::Vec3 mPosition{0.f};
  math::Vec3 mScale{1.f};
  math::Quat mRotation{glm::identity<math::Quat>()};

  mutable bool mIsCacheDirty{false};
  mutable math::Mat4 mTransform{1.f};
};
} // namespace aw::graphics

namespace aw::graphics
{
inline void Transform::position(math::Vec3 pos)
{
  mPosition = pos;
  invalidateCache();
}

inline math::Vec3 Transform::position() const
{
  return mPosition;
}

inline void Transform::scale(math::Vec3 scale)
{
  mScale = scale;
  invalidateCache();
}

inline math::Vec3 Transform::scale() const
{
  return mScale;
}

inline void Transform::rotation(math::Quat rotation)
{
  mRotation = rotation;
  invalidateCache();
}

inline math::Quat Transform::rotation() const
{
  return mRotation;
}

inline void Transform::invalidateCache()
{
  mIsCacheDirty = true;
}
} // namespace aw::graphics
