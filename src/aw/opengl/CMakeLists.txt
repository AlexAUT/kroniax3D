add_to_target(awOpenGL PRIVATE opengl.cpp)

if(AW_OS_DESKTOP)
  add_to_target(awOpenGL PRIVATE impl/opengl43.cpp)
endif()
