#pragma once

#include <aw/opengl/types.hpp>
#include <aw/util/math/matrix.hpp>
#include <aw/util/math/vector.hpp>

namespace aw::graphics
{
class ShaderStage;

class ShaderProgram
{
public:
  ShaderProgram();
  ~ShaderProgram();

  template <typename... ShaderStages>
  bool link(ShaderStages&&... shaderStages);

  GLuint id() const { return mId; }
  bool linked() const { return mLinked; }

  void bind();
  void unbind();

  GLint getUniformLocation(const char* name);

  void set(const char* name, const math::Mat4& mat);
  void set(GLint location, const math::Mat4& mat);

private:
  void attach(const ShaderStage& shaderStage);
  bool link();
  void detach(const ShaderStage& shaderStage);

private:
  GLuint mId;
  bool mLinked{false};
};

template <typename... ShaderStages>
bool ShaderProgram::link(ShaderStages&&... shaderStages)
{
  (attach(shaderStages), ...);
  return link();
  (detach(shaderStages), ...);
}

} // namespace aw::graphics
