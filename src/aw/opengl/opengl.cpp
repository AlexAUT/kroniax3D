#include <aw/opengl/opengl.hpp>

#include <aw/util/log/log.hpp>
#include <aw/util/log/module.hpp>

#include <string>

namespace aw::opengl
{
namespace priv
{
aw::log::Module openglLogModule("OpenGL");

GLenum glCheckError(const char* stmt, const char* file, int line, const char* func)
{
  GLenum errorCode;
  while ((errorCode = glGetError()) != GL_NO_ERROR)
  {
    std::string message;
    switch (errorCode)
    {
    case GL_INVALID_ENUM:
      message = "INVALID_ENUM";
      break;
    case GL_INVALID_VALUE:
      message = "INVALID_VALUE";
      break;
    case GL_INVALID_OPERATION:
      message = "INVALID_OPERATION";
      break;
#ifdef GL_STACK_OVERFLOW
    case GL_STACK_OVERFLOW:
      message = "STACK_OVERFLOW";
      break;
#endif
#ifdef GL_STACK_UNDERFLOW
    case GL_STACK_UNDERFLOW:
      message = "STACK_UNDERFLOW";
      break;
#endif
    case GL_OUT_OF_MEMORY:
      message = "OUT_OF_MEMORY";
      break;
#ifdef GL_INVALID_FRAMEBUFFER_OPERATION
    case GL_INVALID_FRAMEBUFFER_OPERATION:
      message = "INVALID_FRAMEBUFFER_OPERATION";
      break;
#endif
    default:
      message = "UNKNOWN OPENGL ERROR, CODE: " + std::to_string(errorCode);
    }
    aw::log::getDefaultLogger()->log(openglLogModule, file, line, func, log::Level::Warning,
                                     "{} at {} in {} {} {}\n", message, stmt, file, line);
  }
  return GL_NO_ERROR;
}

} // namespace priv
} // namespace aw::opengl
