#pragma once

class Ship;

class ShipController
{
public:
  void update(float dt, Ship& ship);

  void steerUp(bool value);

private:
  float mUpForce{1.20f};

  bool mIsSteeringUp;
};
