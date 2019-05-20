#include <aw/graphics/core/shaderStage.hpp>

#include <aw/graphics/log.hpp>
#include <aw/opengl/opengl.hpp>
#include <aw/util/file/converters.hpp>
#include <aw/util/file/inputStream.hpp>

#include <cassert>

namespace aw::gpu
{
GLenum typeToGL(ShaderStage::Type type);

ShaderStage::ShaderStage(Type type) : mType(type), mId(GL_CHECK(glCreateShader(typeToGL(mType)))) {}

ShaderStage::~ShaderStage()
{
  GL_CHECK(glDeleteShader(mId));
}

bool ShaderStage::loadFromPath(std::string_view path)
{
  file::InputStream file(path);

  if (!file.isOpen())
  {
    LOG_GRAPHICS_E("Failed to open shader file: {}\n", path);
    return false;
  }

  auto content = file::toString(file);
  return loadFromMemory(content.data());
}

bool ShaderStage::loadFromMemory(const char* content)
{
  const char** ptr = &content;
  return loadFromMemory(ptr, 1);
}

bool ShaderStage::loadFromMemory(const char** content, size_t count)
{
  assert(content);

  GL_CHECK(glShaderSource(mId, count, content, nullptr));
  GL_CHECK(glCompileShader(mId));

  int success;
  glGetShaderiv(mId, GL_COMPILE_STATUS, &success);
  if (!success)
  {
    char infoLog[512];
    glGetShaderInfoLog(mId, 512, nullptr, infoLog);
    GL_CHECK(glDeleteShader(mId));
    LOG_GRAPHICS_E("Failed compiling shader stage: {}\n, content: \n\n", infoLog);
    for (size_t i = 0; i < count; i++)
    {
      LOG_GRAPHICS_E("\n{}\n", content[i]);
    }
    return false;
  }
  return true;
}

GLenum typeToGL(ShaderStage::Type type)
{
  using Type = ShaderStage::Type;
  switch (type)
  {
  case Type::Vertex:
    return GL_VERTEX_SHADER;
  case Type::Fragment:
    return GL_FRAGMENT_SHADER;
  default:
    assert(false && "Unsupported shader stage!");
    return GL_NONE;
  }
}
} // namespace aw::gpu
