#pragma once

#include <aw/util/reflection/typeDescriptor.hpp>
#include <aw/util/reflection/typeResolver.hpp>

#include <vector>

namespace aw::reflect
{
class VectorTypeDescriptorBase
{
};

template <typename Descriptor>
constexpr bool isVector()
{
  return std::is_base_of_v<VectorTypeDescriptorBase, Descriptor>;
}

template <typename Descriptor>
constexpr bool isVector(const Descriptor& descriptor)
{
  return isVector<Descriptor>();
}

template <class ElementT>
class VectorTypeDescriptor : public TypeDescriptor, public VectorTypeDescriptorBase
{
public:
  using UnderlyingType = std::vector<ElementT>;
  using value_type = ElementT;

public:
  VectorTypeDescriptor(std::string type) :
      TypeDescriptor(std::string("std::vector<") + type + ">", sizeof(std::string))
  {
  }

  std::vector<ElementT>& value(std::vector<ElementT>& vector) { return vector; }
};

// Partially specialize TypeResolver<> for std::vectors:
template <typename T>
class TypeResolver<std::vector<T>>
{
public:
  using type = VectorTypeDescriptor<T>;
  static TypeDescriptor& get()
  {
    static VectorTypeDescriptor<T> typeDesc;
    return typeDesc;
  }
};

} // namespace aw::reflect
