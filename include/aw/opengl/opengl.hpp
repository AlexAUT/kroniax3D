#pragma once

#include <aw/config.hpp>

#if defined(AW_OS_WINDOWS) || defined(AW_OS_LINUX) || defined(AW_OS_MAC)
#include <aw/opengl/impl/opengl43.hpp>
#endif

namespace aw
{

#define vOffsetof(struct_, member_) reinterpret_cast<const void*>(offsetof(struct_, member_))

namespace opengl
{

namespace priv
{
GLenum glCheckError(const char* stmt, const char* file, int line);

} // namespace priv
} // namespace opengl
} // namespace aw

#ifdef _DEBUG
#define GL_CHECK(stmt)                                                                             \
  do                                                                                               \
  {                                                                                                \
    stmt;                                                                                          \
    aw::opengl::priv::glCheckError(#stmt, __FILE__, __LINE__, __func__);                           \
  } while (false)
#else
#define GL_CHECK(stmt) stmt
#endif
