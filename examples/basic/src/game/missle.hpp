#pragma once

#include <aw/graphics/core/transform.hpp>

class Ship;

class Missle
{
public:
  Missle(const Ship& origin);

  void update(float dt);

  aw::Transform& transform();
  const aw::Transform& transform() const;

private:
private:
  const Ship& mShip;

  float mSpeed{5.f};

  aw::Transform mTransform;
};
