#pragma once

#include <aw/opengl/types.hpp>

#include <aw/graphics/core/bindType.hpp>
#include <aw/graphics/core/usageType.hpp>

namespace aw
{

class GPUBufferObject
{
public:
  GPUBufferObject(BindType type);
  GPUBufferObject(BindType type, UsageType usage);
  virtual ~GPUBufferObject();

  GPUBufferObject(const GPUBufferObject&) = delete;
  GPUBufferObject operator=(const GPUBufferObject&) = delete;

  template <typename Container>
  void setData(const Container& container);
  void setData(const void* data, size_t size);

  template <typename Container>
  void setSubData(const Container& container, ptrdiff offset);
  void setSubData(const void* data, size_t size, ptrdiff offset);

  void bind() const;
  void unbind() const;

  unsigned id() const { return mId; }

private:
  GLuint mId;
  GLenum mType;
  GLbitfield mUsage;
};

} // namespace aw

namespace aw
{
template <typename Container>
inline void GPUBufferObject::setData(const Container& container)
{
  constexpr auto elementSize = sizeof(typename Container::value_type);
  setData(container.data(), elementSize * container.size());
}

template <typename Container>
inline void GPUBufferObject::setSubData(const Container& container, ptrdiff offset)
{
  constexpr auto elementSize = sizeof(typename Container::value_type);
  setSubData(container.data(), elementSize * container.size(), offset);
}
} // namespace aw
