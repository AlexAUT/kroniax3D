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
  std::string& value(std::string& string) { return string; }
};

template <>
inline auto& getExternalDescriptor<std::string>()
{
  static StringTypeDescriptor instance;
  return instance;
}
} // namespace aw::reflect
