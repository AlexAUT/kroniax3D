cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)

project(awExampleBasic)
add_executable(${PROJECT_NAME} main.cpp basicState.cpp)

add_subdirectory(src/game)


set(AW_ENGINE_DIR ../../ CACHE STRING "Path to the awEngine git repository")

#set(AW_TESTS OFF CACHE BOOL "Disable tests" FORCE)
set(AW_BUILD_DEPENDENCIES ON CACHE BOOL "Build engine dependencies" FORCE)
enable_testing()
message(STATUS "AWEngine Dir: ${AW_ENGINE_DIR}")
add_subdirectory(${AW_ENGINE_DIR} "awEngine")

enableHTMLOutput()
# Supports emscripten MT
enableEmscriptenMT(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PUBLIC awEngine awOpenGL awUtil)

