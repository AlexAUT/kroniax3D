add_to_target(awOpenGL PUBLIC opengl.hpp)
add_to_target(awOpenGL PUBLIC types.hpp)

if(AW_OS_DESKTOP)
  add_to_target(awOpenGL PRIVATE impl/opengl43.hpp)
endif()
