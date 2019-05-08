#pragma once

#include <aw/util/reflection/reflection.hpp>
#include <aw/util/reflection/typeDescriptor.hpp>
#include <aw/util/reflection/typeResolver.hpp>

#include <aw/util/type/staticForLoop.hpp>

#include <functional>
#include <iostream>
#include <stddef.h>
#include <string>
#include <vector>

namespace aw::reflect
{
template <typename OwningClass, typename MemberType>
class ClassMember
{
public:
  using MemberPtr = MemberType OwningClass::*;
  using ConstMemberPtr = const MemberType OwningClass::*;

  using ConstRefSetter = void (OwningClass::*)(const MemberType&);
  using ValueSetter = void (OwningClass::*)(const MemberType&);

  using ConstRefGetter = const MemberType& (OwningClass::*)(void)const;

  using UnderylingDescriptor = typename TypeResolver<MemberType>::type;

public:
  ClassMember(std::string name, MemberPtr memberPtr) :
      mName(name),
      mHasMemberPtr(true),
      mMemberPtr(memberPtr),
      mConstMemberPtr(memberPtr)
  {
  }

  ClassMember(std::string name, ConstRefGetter getter) : mName(name), mConstRefGetter(getter) {}

  constexpr std::string_view name() const { return mName; }
  MemberType& value(OwningClass& instance) { return instance.*mMemberPtr; }

  static inline auto& underlyingDescriptor() { return TypeResolver<MemberType>::get(); }

private:
  std::string mName;
  bool mHasMemberPtr{false};
  MemberPtr mMemberPtr{nullptr};
  MemberPtr mConstMemberPtr{nullptr};

  ConstRefGetter mConstRefGetter{nullptr};
};

// Just to make Template handling easier
class ClassTypeDescriptorBase
{
};

template <typename OwningClass, typename... MemberTypes>
class ClassTypeDescriptor : public TypeDescriptor, public ClassTypeDescriptorBase
{
public:
  using Class = OwningClass;

public:
  //  ClassTypeDescriptor(std::string name, size_t size) : TypeDescriptor(name, size) {}
  ClassTypeDescriptor(std::string name, ClassMember<OwningClass, MemberTypes>... members) :
      TypeDescriptor(name, sizeof(OwningClass)),
      mMembers{members...}
  {
  }

  constexpr std::size_t memberCount() const { return sizeof...(MemberTypes); }

  template <typename Function>
  constexpr void forAllMembers(Function&& fun)
  {
    staticFor<sizeof...(MemberTypes)>([this, &fun](auto index) { fun(std::get<index>(mMembers)); });
  }

private:
  std::tuple<ClassMember<OwningClass, MemberTypes>...> mMembers;
};

#define REFLECT() static inline auto& getTypeDescriptor();

#define REFLECT_BEGIN(TypeName)                                                                    \
  template <>                                                                                      \
  inline auto& aw::reflect::getReflection<TypeName>()                                              \
  {                                                                                                \
    using T = TypeName;                                                                            \
    static ClassTypeDescriptor descriptor                                                                              \
  (                                                                                                                    \
#TypeName

#define REFLECT_MEMBER(name) , ClassMember(#name, &T::name)
#define REFLECT_PRIVATE_MEMBER(name, getter) , ClassMember(#name, getter)

#define REFLECT_END(TypeName)                                                                      \
);                                                                                                 \
  return descriptor;                                                                               \
  }                                                                                                \
  auto& TypeName::getTypeDescriptor() { return aw::reflect::getReflection<TypeName>(); }

} // namespace aw::reflect
