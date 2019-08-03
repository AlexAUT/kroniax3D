#pragma once

#include <aw/util/reflection/typeDescriptor.hpp>
#include <aw/util/reflection/typeResolver.hpp>
#include <aw/util/types.hpp>

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
  using UnderlyingType = PrimitiveType;

public:
  PrimitiveTypeDescriptor(const char* name) : TypeDescriptor(name, sizeof(PrimitiveType)) {}

  // To be consistent with other typedescriptors
  PrimitiveType& value(PrimitiveType& type) { return type; }
};

#define CREATE_DESCRIPTOR(Type)                                                                    \
  template <>                                                                                      \
  inline auto& getExternalDescriptor<Type>()                                                       \
  {                                                                                                \
    static PrimitiveTypeDescriptor<Type> instance(#Type);                                          \
    return instance;                                                                               \
  }

CREATE_DESCRIPTOR(bool)

CREATE_DESCRIPTOR(aw::uint8)
CREATE_DESCRIPTOR(aw::uint16)
CREATE_DESCRIPTOR(aw::uint32)
CREATE_DESCRIPTOR(aw::uint64)

CREATE_DESCRIPTOR(aw::int8)
CREATE_DESCRIPTOR(aw::int16)
CREATE_DESCRIPTOR(aw::int32)
CREATE_DESCRIPTOR(aw::int64)
} // namespace aw::reflect
