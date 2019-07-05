#pragma once

class Ship;

class PhysicsController
{
public:
  void update(float dt, Ship& ship);

public:
  float mGravity{0.25f};
};
