#pragma once

#include <aw/opengl/types.hpp>

#include <string_view>

namespace aw::graphics
{
class ShaderStage
{
public:
  enum class Type
  {
    Vertex,
    Fragment,
  };

public:
  ShaderStage(Type type);
  ~ShaderStage();

  bool loadFromPath(std::string_view path);
  bool loadFromMemory(const char* content);
  bool loadFromMemory(const char** content, size_t count);

  GLuint id() const { return mId; }
  Type type() const { return mType; }

private:
private:
  Type mType;
  GLuint mId;
};
} // namespace aw::graphics
