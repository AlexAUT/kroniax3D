# SFML
if(AW_OS_EMSCRIPTEN)
  set(SFML_DIR ${CMAKE_PREFIX_PATH}/lib/cmake/fmt)
elseif(AW_OS_ANDROID)
  set(SFML_DIR ${CMAKE_PREFIX_PATH}/lib/${ANDROID_ABI}/cmake/fmt)
endif()
find_package(SFML REQUIRED COMPONENTS network window system)

target_link_libraries(awEngine PUBLIC awGraphics awOpenGL awUtil sfml-network sfml-window sfml-system)

enableEmscriptenMT(awEngine)
