#include "ship.hpp"

#include <aw/util/math/constants.hpp>

#include <glm/gtx/quaternion.hpp>

Ship::Ship() {}

void Ship::velocityDir(aw::Vec3 velocityDir)
{
  mVelocityDir = velocityDir;
}

aw::Vec3 Ship::velocityDir() const
{
  return mVelocityDir;
}

void Ship::velocity(float velocity)
{
  mVelocity = velocity;
}

float Ship::velocity() const
{
  return mVelocity;
}

aw::Transform& Ship::transform()
{
  return mTransform;
}

const aw::Transform& Ship::transform() const
{
  return mTransform;
}

void Ship::update(float dt)
{
  auto pos = mTransform.position();
  pos += mVelocityDir * mVelocity * dt;

  mTransform.position(pos);

  mTransform.rotation(glm::quatLookAt(mVelocityDir, aw::Vec3{0.f, 1.f, 0.f}));
}

