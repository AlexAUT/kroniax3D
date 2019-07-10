
#include <aw/graphics/core/vertexArrayObject.hpp>

#include <aw/config.hpp>
#include <aw/graphics/core/bufferObject.hpp>
#include <aw/opengl/opengl.hpp>

#include <cassert>

namespace aw
{
VertexArrayObject::VertexArrayObject()
{
  GL_CHECK(glGenVertexArrays(1, &mVAOHandle));
}

VertexArrayObject::~VertexArrayObject()
{
  GL_CHECK(glDeleteVertexArrays(1, &mVAOHandle));
}

void VertexArrayObject::bind() const
{
  GL_CHECK(glBindVertexArray(mVAOHandle));
}

void VertexArrayObject::unbind() const
{
  GL_CHECK(glBindVertexArray(0));
}

void VertexArrayObject::addVertexAttribute(const GPUBufferObject* vbo, VertexAttribute attribute)
{
  if (vbo)
    vbo->bind();

  GL_CHECK(glEnableVertexAttribArray(attribute.index));
  GL_CHECK(glVertexAttribPointer(attribute.index, attribute.size, attribute.type,
                                 attribute.normalized, attribute.stride, attribute.offset));
}

} // namespace aw
