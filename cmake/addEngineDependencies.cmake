# SFML
if(AW_OS_EMSCRIPTEN)
  set(SFML_DIR ${CMAKE_PREFIX_PATH}/lib/cmake/SFML)
elseif(AW_OS_ANDROID)
  set(SFML_DIR ${ANDROID_NDK}/sources/third_party/sfml/lib/${ANDROID_ABI}/cmake/SFML)
endif()
message(STATUS "SFML PATH: ${SFML_DIR}")
find_package(SFML REQUIRED COMPONENTS window system)

target_link_libraries(awEngine PUBLIC sfml-window sfml-system awUtil awOpenGL)


enableEmscriptenMT(awEngine)
