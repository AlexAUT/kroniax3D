#pragma once

#include <aw/opengl/types.hpp>
#include <aw/util/color.hpp>
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

  void bind() const;
  void unbind() const;

  GLint getUniformLocation(const char* name) const;

  void set(const char* name, const math::Mat4& mat) const;
  void set(GLint location, const math::Mat4& mat) const;

  void set(const char* name, const math::Vec2& vec) const;
  void set(GLint location, const math::Vec2& vec) const;

  void set(const char* name, const math::Vec3& vec) const;
  void set(GLint location, const math::Vec3& vec) const;

  void set(const char* name, const math::Vec4& vec) const;
  void set(GLint location, const math::Vec4& vec) const;

  void set(const char* name, const Color& color) const;
  void set(GLint location, const Color& color) const;

  void set(const char* name, int value) const;
  void set(GLint location, int value) const;

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
