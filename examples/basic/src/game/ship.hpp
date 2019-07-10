#pragma once

#include <aw/graphics/core/transform.hpp>
#include <aw/util/math/vector.hpp>

class Ship
{
public:
  Ship();

  aw::Transform& transform();
  const aw::Transform& transform() const;

  void velocityDir(aw::Vec3 velocityDir);
  aw::Vec3 velocityDir() const;

  void velocity(float velocity);
  float velocity() const;

  void update(float dt);

private:
  aw::Transform mTransform;

  aw::Vec3 mVelocityDir{0.f};
  float mVelocity{0.f};
};
