#include "shipController2.hpp"

#include "../../logApp.hpp"
#include "ship.hpp"

void ShipController2::setShip(Ship* ship)
{
  mShip = ship;
}

void ShipController2::rotateLeft()
{
  mRotationSteps = mRotationSteps == 0 ? mNumSteps - 1 : mRotationSteps - 1;
}

void ShipController2::rotateRight()
{
  mRotationSteps = (mRotationSteps + 1) % mNumSteps;
}

void ShipController2::update(float dt)
{
  if (!mShip)
    return;

  auto currentDir = mShip->velocityDir();
  auto currentAngle = glm::acos(glm::dot(currentDir, aw::Vec3{0.f, 0.f, -1.f}));
  if (currentDir.x < 0)
    currentAngle = 2 * aw::pi() - currentAngle;

  auto wantedAngle = aw::pi_4() + mRotationSteps * mRotationStepSize;

  auto diff = wantedAngle - currentAngle;

  if (diff < -aw::pi())
  {
    diff += 2 * aw::pi();
  }
  if (diff > aw::pi())
  {
    diff -= 2 * aw::pi();
  }

  LOG_APP_D("d {} c {} w {}", diff, currentAngle, wantedAngle);

  auto stepSize = mRotationSpeed * dt;

  float angle = 0.f;
  if (std::abs(diff) < stepSize)
    angle = wantedAngle;
  else
    angle = currentAngle + std::copysign(stepSize, diff);

  aw::Vec3 v{glm::sin(angle), 0.f, -glm::cos(angle)};
  if (mShip)
    mShip->velocityDir(glm::normalize(v));
}
