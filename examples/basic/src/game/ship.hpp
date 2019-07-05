#pragma once

#include <aw/graphics/core/transform.hpp>
#include <aw/util/math/vector.hpp>

class Ship
{
public:
  Ship();

  aw::graphics::Transform& transform();
  const aw::graphics::Transform& transform() const;

  void velocityDir(aw::math::Vec3 velocityDir);
  aw::math::Vec3 velocityDir() const;

  void velocity(float velocity);
  float velocity() const;

  void update(float dt);

private:
  aw::graphics::Transform mTransform;

  aw::math::Vec3 mVelocityDir{0.f};
  float mVelocity{0.f};
};
