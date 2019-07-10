#pragma once

#include <aw/util/math/matrix.hpp>
#include <aw/util/math/quat.hpp>
#include <aw/util/math/vector.hpp>

namespace aw
{
class Transform
{
public:
  void position(Vec3 pos);
  Vec3 position() const;

  void scale(Vec3 scale);
  Vec3 scale() const;

  void rotation(Quat rotation);
  Quat rotation() const;

  const Mat4& toMatrix() const;

private:
  void invalidateCache();

private:
  Vec3 mPosition{0.f};
  Vec3 mScale{1.f};
  Quat mRotation{glm::identity<Quat>()};

  mutable bool mIsCacheDirty{false};
  mutable Mat4 mTransform{1.f};
};
} // namespace aw

namespace aw
{
inline void Transform::position(Vec3 pos)
{
  mPosition = pos;
  invalidateCache();
}

inline Vec3 Transform::position() const
{
  return mPosition;
}

inline void Transform::scale(Vec3 scale)
{
  mScale = scale;
  invalidateCache();
}

inline Vec3 Transform::scale() const
{
  return mScale;
}

inline void Transform::rotation(Quat rotation)
{
  mRotation = rotation;
  invalidateCache();
}

inline Quat Transform::rotation() const
{
  return mRotation;
}

inline void Transform::invalidateCache()
{
  mIsCacheDirty = true;
}
} // namespace aw
