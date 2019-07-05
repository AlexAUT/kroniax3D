#pragma once

class Ship;

class ShipController
{
public:
  void update(float dt, Ship& ship);

  void steerUp(bool value);

private:
  float mUpForce{0.75f};

  bool mIsSteeringUp;
};
