#pragma once

#include <aw/util/reflection/typeDescriptorClass.hpp>
#include <aw/util/reflection/types/primitiveTypes.hpp>

#include <type_traits>

namespace aw::reflect
{
template <
    typename TypeDesc, typename Instance, typename Archive,
    typename std::enable_if_t<std::is_base_of_v<aw::reflect::PrimitiveTypeDescriptorBase, TypeDesc>,
                              int>* = nullptr>
void serialize(TypeDesc& desc, Instance& instance, Archive& archive)
{
  static_assert(!std::is_const<TypeDesc>::value, "TEST ASSERT");
  archive(desc.value(instance));
}
template <
    typename TypeDesc, typename Instance, typename Archive,
    typename std::enable_if_t<std::is_base_of_v<aw::reflect::PrimitiveTypeDescriptorBase, TypeDesc>,
                              int>* = nullptr>
void serialize(TypeDesc& desc, Instance instance, Archive& archive)
{
  static_assert(!std::is_const<TypeDesc>::value, "TEST ASSERT");
  archive(desc.value(instance));
}

template <typename TypeDesc, typename Instance, typename Archive,
          typename std::enable_if_t<
              std::is_base_of_v<aw::reflect::ClassTypeDescriptorBase, TypeDesc>, int>* = nullptr>
void serialize(TypeDesc& desc, Instance& instance, Archive& archive)
{
  // archive.setNextName(desc.name().data());
  archive.startNode();

  desc.forAllMembers([&instance, &archive](auto& mem) {
    auto& memTypeDesc = mem.underlyingDescriptor();
    archive.setNextName(mem.name().data());
    serialize(mem.underlyingDescriptor(), mem.value(instance), archive);
  });

  archive.finishNode();
}

template <typename TypeDesc, typename Instance, typename Archive,
          typename std::enable_if_t<
              std::is_base_of_v<aw::reflect::ClassTypeDescriptorBase, TypeDesc>, int>* = nullptr>
void parse(TypeDesc& desc, Instance& instance, Archive& archive)
{
  desc.forAllMembers([&instance, &archive](auto& mem) {
    auto& memTypeDesc = mem.underlyingDescriptor();
    reflect(mem.underlyingDescriptor(), mem.value(instance), archive);
  });
}
} // namespace aw::reflect
