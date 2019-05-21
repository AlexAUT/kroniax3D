#pragma once

#include <aw/graphics/core/vertexAttribute.hpp>
#include <aw/graphics/core/vertexLayout.hpp>
#include <aw/opengl/types.hpp>

namespace aw::graphics
{
class BufferObject;

class VertexArrayObject
{
public:
  VertexArrayObject();
  ~VertexArrayObject();
  VertexArrayObject(const VertexArrayObject&) = delete;
  VertexArrayObject operator=(const VertexArrayObject&) = delete;

  void bind() const;
  void unbind() const;

  void addVertexAttribute(const BufferObject* vbo, VertexAttribute attribute);

  template <size_t T>
  void addVertexAttributes(const BufferObject* vbo, const VertexLayout<T>& layout);

  GLuint id() const { return mVAOHandle; }

private:
  GLuint mVAOHandle;
};

template <size_t T>
void VertexArrayObject::addVertexAttributes(const BufferObject* vbo, const VertexLayout<T>& layout)
{
  for (const auto& a : layout)
    addVertexAttribute(vbo, a);
}

} // namespace aw::graphics
