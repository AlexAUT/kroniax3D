#pragma once

#include <aw/util/reflection/typeDescriptor.hpp>
#include <aw/util/reflection/typeResolver.hpp>

#include <type_traits>

namespace aw::reflect
{
class EnumTypeDescriptorBase
{
};

template <typename Descriptor>
constexpr bool isEnum()
{
  return std::is_base_of_v<EnumTypeDescriptorBase, Descriptor>;
}

template <typename Descriptor>
constexpr bool isEnum(const Descriptor& descriptor)
{
  return isEnum<Descriptor>();
}

template <typename Enum>
class EnumTypeDescriptor : public TypeDescriptor, public EnumTypeDescriptorBase
{
public:
  using UnderlyingType = typename std::underlying_type_t<Enum>;
  using EnumType = Enum;

public:
  EnumTypeDescriptor(const char* name) : TypeDescriptor(name, sizeof(Enum)) {}

  // To be consistent with other typedescriptors
  Enum& value(Enum& enumValue) { return enumValue; }
};
} // namespace aw::reflect

#define REFLECT_ENUM(EnumName)                                                                     \
  namespace aw::reflect                                                                            \
  {                                                                                                \
  template <>                                                                                      \
  inline auto& getExternalDescriptor<EnumName>()                                                   \
  {                                                                                                \
    static EnumTypeDescriptor<EnumName> instance(#EnumName);                                       \
    return instance;                                                                               \
  }                                                                                                \
  template <>                                                                                      \
  inline auto& getReflection<EnumName>()                                                           \
  {                                                                                                \
    return getExternalDescriptor<EnumName>();                                                      \
  }                                                                                                \
  }

