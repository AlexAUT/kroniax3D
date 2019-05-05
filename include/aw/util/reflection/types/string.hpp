#pragma once

#include <aw/util/reflection/typeDescriptor.hpp>
#include <aw/util/reflection/typeResolver.hpp>

#include <string>

namespace aw::reflect
{
class StringTypeDescriptor : public TypeDescriptor
{
public:
  StringTypeDescriptor() : TypeDescriptor("std::string", sizeof(std::string)) {}

  // To be consistent with other typedescriptors
  const std::string& getValue(const std::string& string) const { return string; }
};

template <>
auto& getExternalDescriptor<std::string>()
{
  static StringTypeDescriptor instance;
  return instance;
}
} // namespace aw::reflect
