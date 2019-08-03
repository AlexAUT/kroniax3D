#pragma once

#include <aw/util/reflection/reflection.hpp>
#include <aw/util/reflection/typeDescriptorClass.hpp>

namespace aw::reflect
{
template <typename ReflectedType, typename Stream>
void toStream(Stream& stream, ReflectedType& instance, int ident = 0)
{
  auto refl = aw::reflect::getReflection<ReflectedType>();
  stream << refl.name() << ": {\n";
  refl.forAllMembers([&](auto member) {
    if constexpr (isClass(member))
    {
      stream << "Subclasses not implemented yet!\n";
    }
    else
    {
      if constexpr (isOfType<aw::uint8>(member))
      {
        stream << "\t" << member.name() << ": " << static_cast<unsigned>(member.value(instance))
               << "\n";
      }
      else
      {
        stream << "\t" << member.name() << ": " << member.value(instance) << "\n";
      }
    }
  });
  stream << "}" << std::endl;
}
} // namespace aw::reflect
