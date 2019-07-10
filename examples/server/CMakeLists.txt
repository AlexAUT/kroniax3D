cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)

project(awServerExample)
add_executable(${PROJECT_NAME})

add_subdirectory(src)

set(AW_ENGINE_DIR ../../ CACHE STRING "Path to the awEngine git repository")

enable_testing()
message(STATUS "AWEngine Dir: ${AW_ENGINE_DIR}")
add_subdirectory(${AW_ENGINE_DIR} "awEngine")

enableHTMLOutput()
# Supports emscripten MT
enableEmscriptenMT(${PROJECT_NAME})
target_link_libraries(${PROJECT_NAME} PUBLIC awEngine awOpenGL awUtil)

