#pragma once

#include <aw/opengl/types.hpp>

namespace aw::gpu
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

} // namespace aw::gpu
