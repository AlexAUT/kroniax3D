#pragma once

#include <aw/util/log/level.hpp>

#include <string>

namespace aw::log
{
struct Message;

class Sink
{
public:
  virtual void log(const Message& msg) = 0;

private:
private:
};
} // namespace aw::log
