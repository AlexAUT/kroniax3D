#pragma once

enum MessageType
{
  Init,
  GameTick,
};

class GameMessage
{
  MessageType type;
};
