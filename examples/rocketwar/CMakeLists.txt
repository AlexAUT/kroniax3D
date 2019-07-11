cmake_minimum_required(VERSION 3.10)

set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)

project(rocketwars)
add_executable(${PROJECT_NAME}_game)
add_subdirectory(src/game)
target_include_directories(${PROJECT_NAME}_game PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_executable(${PROJECT_NAME}_server)
add_subdirectory(src/server)
target_include_directories(${PROJECT_NAME}_server PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/src)

add_subdirectory(src/shared)


set(AW_ENGINE_DIR ../../ CACHE STRING "Path to the awEngine git repository")

#set(AW_TESTS OFF CACHE BOOL "Disable tests" FORCE)
set(AW_BUILD_DEPENDENCIES ON CACHE BOOL "Build engine dependencies" FORCE)
enable_testing()
message(STATUS "AWEngine Dir: ${AW_ENGINE_DIR}")
add_subdirectory(${AW_ENGINE_DIR} "awEngine")

enableHTMLOutput()
# Supports emscripten MT
enableEmscriptenMT(${PROJECT_NAME}_game)
enableEmscriptenMT(${PROJECT_NAME}_server)
target_link_libraries(${PROJECT_NAME}_game PUBLIC awEngine awOpenGL awUtil)
target_link_libraries(${PROJECT_NAME}_server PUBLIC awEngine awOpenGL awUtil)

