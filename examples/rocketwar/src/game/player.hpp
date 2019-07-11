#pragma once

#include <aw/util/types.hpp>

#include "shared/ship.hpp"

class Player
{
public:
  Player() = default;
  Player(aw::uint64 id);

  aw::uint64 id() const;

  Ship& ship();

  bool owner() const;
  void owner(bool value);

private:
private:
  aw::uint64 mClientId{0};

  Ship mShip;

  bool mOwner{false};
};
