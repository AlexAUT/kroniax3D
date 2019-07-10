#include "shipController.hpp"

#include "ship.hpp"

void ShipController::update(float dt, Ship& ship)
{
  if (!mIsSteeringUp)
    return;
  auto dir = ship.velocityDir();
  dir += aw::Vec3{0.f, 1.f, 0.f} * mUpForce * dt;
  ship.velocityDir(glm::normalize(dir));
}

void ShipController::steerUp(bool value)
{
  mIsSteeringUp = value;
}
