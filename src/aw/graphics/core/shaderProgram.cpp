#include <aw/graphics/core/shaderProgram.hpp>

#include <aw/graphics/core/shaderStage.hpp>
#include <aw/graphics/log.hpp>
#include <aw/opengl/opengl.hpp>
#include <aw/util/math/matrix.hpp>

namespace aw
{
ShaderProgram::ShaderProgram() : mId(GL_CHECK(glCreateProgram())) {}

ShaderProgram::~ShaderProgram()
{
  GL_CHECK(glDeleteProgram(mId));
}

void ShaderProgram::attach(const ShaderStage& stage)
{
  GL_CHECK(glAttachShader(mId, stage.id()));
}

bool ShaderProgram::link()
{
  GL_CHECK(glLinkProgram(mId));

  int success;
  GL_CHECK(glGetProgramiv(mId, GL_LINK_STATUS, &success));
  if (!success)
  {
    char infoLog[512];
    GL_CHECK(glGetProgramInfoLog(mId, 512, nullptr, infoLog));
    LOG_GRAPHICS_E("Failed to link program: {}\n", infoLog);
    return false;
  }
  // If the program is already linked but failed in a second call stay linked (open behaviour)
  mLinked = true;
  return true;
}

void ShaderProgram::bind() const
{
  assert(mLinked && "You have to link the program before using it");
  GL_CHECK(glUseProgram(mId));
}

void ShaderProgram::detach(const ShaderStage& shaderStage)
{
  GL_CHECK(glDetachShader(mId, shaderStage.id()));
}

GLint ShaderProgram::getUniformLocation(const char* name) const
{
  GLint loc;
  GL_CHECK(loc = glGetUniformLocation(mId, name));
  return loc;
}

void ShaderProgram::set(const char* name, const Mat4& mat) const
{
  set(getUniformLocation(name), mat);
}

void ShaderProgram::set(GLint location, const Mat4& mat) const
{
  GL_CHECK(glUniformMatrix4fv(location, 1, GL_FALSE, &mat[0][0]));
}
void ShaderProgram::set(const char* name, const Vec2& vec) const
{
  set(getUniformLocation(name), vec);
}

void ShaderProgram::set(GLint location, const Vec2& vec) const
{
  GL_CHECK(glUniform2f(location, vec.x, vec.y));
}

void ShaderProgram::set(const char* name, const Vec3& vec) const
{
  set(getUniformLocation(name), vec);
}

void ShaderProgram::set(GLint location, const Vec3& vec) const
{

  GL_CHECK(glUniform3f(location, vec.x, vec.y, vec.z));
}

void ShaderProgram::set(const char* name, const Vec4& vec) const
{
  set(getUniformLocation(name), vec);
}

void ShaderProgram::set(GLint location, const Vec4& vec) const
{
  GL_CHECK(glUniform4f(location, vec.x, vec.y, vec.z, vec.w));
}

void ShaderProgram::set(const char* name, const Color& color) const
{
  set(getUniformLocation(name), color);
}

void ShaderProgram::set(GLint location, const Color& color) const
{
  GL_CHECK(glUniform4f(location, color.r, color.g, color.b, color.a));
}
void ShaderProgram::set(const char* name, int value) const
{
  set(getUniformLocation(name), value);
}

void ShaderProgram::set(GLint location, int value) const
{
  GL_CHECK(glUniform1i(location, value));
}

} // namespace aw
