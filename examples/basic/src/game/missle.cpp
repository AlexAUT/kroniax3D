#include "missle.hpp"

#include "ship.hpp"

Missle::Missle(const Ship& controller) : mShip(controller)
{
  mTransform = mShip.transform();
}

void Missle::update(float dt)
{
  mTransform.rotation(mShip.transform().rotation());

  auto pos = mTransform.position() + mShip.velocityDir() * mSpeed * dt;
  mTransform.position(pos);
}

aw::Transform& Missle::transform()
{
  return mTransform;
}

const aw::Transform& Missle::transform() const
{
  return mTransform;
}
