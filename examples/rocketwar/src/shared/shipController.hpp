#pragma once

#include <aw/util/math/constants.hpp>
#include <aw/util/math/vector.hpp>

#include <cmath>

class Ship;

class ShipController
{
public:
  void setShip(Ship* ship);

  void rotateLeft();
  void rotateRight();

  void update(float dt);

private:
  Ship* mShip{nullptr};

  int mRotationSteps{0};
  float mRotationStepSize{aw::pi_2()};
  int mNumSteps{static_cast<int>(std::round((2 * aw::pi()) / aw::pi_2()))};

  float mRotationSpeed{7.f};
};
