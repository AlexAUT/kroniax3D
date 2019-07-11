#include "player.hpp"

Player::Player(aw::uint64 id) : mClientId{id} {}

aw::uint64 Player::id() const
{
  return mClientId;
}

Ship& Player::ship()
{
  return mShip;
}

bool Player::owner() const
{
  return mOwner;
}

void Player::owner(bool value)
{
  mOwner = value;
}
