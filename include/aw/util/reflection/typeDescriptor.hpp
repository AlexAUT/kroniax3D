#pragma once

#include <string>

namespace aw::reflect
{

class TypeDescriptor
{
public:
  TypeDescriptor(std::string name, unsigned size) : mName{name}, mSize{size} {};
  virtual ~TypeDescriptor(){};

  std::string_view name() const { return mName; }
  unsigned size() const { return mSize; }

private:
  std::string mName;
  unsigned mSize;
};

} // namespace aw::reflect
