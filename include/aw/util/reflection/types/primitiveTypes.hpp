#pragma once

#include <aw/util/reflection/typeDescriptor.hpp>
#include <aw/util/reflection/typeResolver.hpp>

#include <iostream>

namespace aw::reflect
{
class PrimitiveTypeDescriptorBase
{
};

template <typename PrimitiveType>
class PrimitiveTypeDescriptor : public TypeDescriptor, public PrimitiveTypeDescriptorBase
{
public:
  PrimitiveTypeDescriptor(const char* name) : TypeDescriptor(name, sizeof(PrimitiveType)) {}

  // To be consistent with other typedescriptors
  PrimitiveType& value(PrimitiveType& type) { return type; }
};
template <>
inline auto& getExternalDescriptor<bool>()
{
  static PrimitiveTypeDescriptor<bool> instance("bool");
  return instance;
}

template <>
inline auto& getExternalDescriptor<char>()
{
  static PrimitiveTypeDescriptor<char> instance("char");
  return instance;
}

template <>
inline auto& getExternalDescriptor<unsigned char>()
{
  static PrimitiveTypeDescriptor<char> instance("uchar");
  return instance;
}

template <>
inline auto& getExternalDescriptor<int>()
{
  static PrimitiveTypeDescriptor<int> instance("int");
  return instance;
}

template <>
inline auto& getExternalDescriptor<unsigned>()
{
  static PrimitiveTypeDescriptor<unsigned> instance("uint");
  return instance;
}

template <>
inline auto& getExternalDescriptor<float>()
{
  static PrimitiveTypeDescriptor<float> instance("float");
  return instance;
}

template <>
inline auto& getExternalDescriptor<double>()
{
  static PrimitiveTypeDescriptor<double> instance("double");
  return instance;
}
} // namespace aw::reflect
