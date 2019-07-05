#include "ship.hpp"

Ship::Ship() {}

void Ship::velocityDir(aw::math::Vec3 velocityDir)
{
  mVelocityDir = velocityDir;
}

aw::math::Vec3 Ship::velocityDir() const
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

aw::graphics::Transform& Ship::transform()
{
  return mTransform;
}

const aw::graphics::Transform& Ship::transform() const
{
  return mTransform;
}

void Ship::update(float dt)
{
  auto pos = mTransform.position();
  pos += mVelocityDir * mVelocity * dt;

  mTransform.position(pos);
}

