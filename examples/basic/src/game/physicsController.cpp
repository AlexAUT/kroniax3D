#include "physicsController.hpp"

#include "ship.hpp"

void PhysicsController::update(float dt, Ship& ship)
{
  auto dir = ship.velocityDir();
  dir += aw::math::Vec3{0.f, -1.f, 0.f} * mGravity * dt;
  ship.velocityDir(glm::normalize(dir));
}
