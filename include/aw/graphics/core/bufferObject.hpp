#pragma once

#include <aw/opengl/types.hpp>

#include <aw/graphics/core/bindType.hpp>
#include <aw/graphics/core/usageType.hpp>

namespace aw::gpu
{

class BufferObject
{
public:
  BufferObject(BindType type);
  BufferObject(BindType type, UsageType usage);
  virtual ~BufferObject();

  BufferObject(const BufferObject&) = delete;
  BufferObject operator=(const BufferObject&) = delete;

  void setData(const void* data, size_t size);
  template <typename Container>
  void setData(const Container& container);

  void setSubData(const void* data, size_t size, ptrdiff offset);
  template <typename Container>
  void setSubData(const Container& container, ptrdiff offset);

  void bind() const;
  void unbind() const;

  unsigned id() const { return mId; }

private:
  GLuint mId;
  GLenum mType;
  GLbitfield mUsage;
};

} // namespace aw::gpu

namespace aw::gpu
{
template <typename Container>
inline void BufferObject::setData(const Container& container)
{
  constexpr auto elementSize = sizeof(Container::value_type);
  setData(container.data(), container.size() * elementSize);
}

template <typename Container>
inline void BufferObject::setSubData(const Container& container, ptrdiff offset)
{
  constexpr auto elementSize = sizeof(Container::value_type);
  setData(container.data(), container.size() * elementSize, offset);
}
} // namespace aw::gpu
