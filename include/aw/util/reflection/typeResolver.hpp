#pragma once

#include <aw/util/reflection/typeDescriptor.hpp>

#include <type_traits>

namespace aw::reflect
{

class TypeDescriptor;

// Declare the function template that handles primitive types such as int, std::string, etc.:
template <typename T>
auto& getExternalDescriptor();

/*
template <typename T>
auto& getPrimitiveDescriptor()
{
  static TypeDescriptor t("t", 0);
  return t;
}
*/

// A helper class to find TypeDescriptors in different ways:
struct DefaultResolver
{
  template <typename T>
  static char func(std::add_pointer_t<decltype(T::getTypeDescriptor())>);
  template <typename T>
  static int func(...);
  template <typename T>
  struct IsReflected
  {
    enum
    {
      value = (sizeof(func<T>(nullptr)) == sizeof(char))
    };
  };

  // This version is called if T has a static member named "Reflection":
  template <typename T, typename std::enable_if<IsReflected<T>::value, int>::type = 0>
  static auto& get()
  {
    return T::getTypeDescriptor();
  }

  // This version is called otherwise:
  template <typename T, typename std::enable_if<!IsReflected<T>::value, int>::type = 0>
  static auto& get()
  {
    return getExternalDescriptor<T>();
  }
};

template <typename T>
class TypeResolver
{
public:
  using type = decltype(DefaultResolver::get<T>());
  static auto& get() { return DefaultResolver::get<T>(); }
};

} // namespace aw::reflect
