#include <aw/graphics/core/shaderProgram.hpp>

#include <aw/graphics/core/shaderStage.hpp>
#include <aw/graphics/log.hpp>
#include <aw/opengl/opengl.hpp>

namespace aw::gpu
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

void ShaderProgram::bind()
{
  assert(mLinked && "You have to link the program before using it");
  GL_CHECK(glUseProgram(mId));
}

void ShaderProgram::detach(const ShaderStage& shaderStage)
{
  GL_CHECK(glDetachShader(mId, shaderStage.id()));
}

} // namespace aw::gpu
