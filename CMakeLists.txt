cmake_minimum_required(VERSION 3.10)

include(cmake/enableWarnings.cmake)
include(cmake/addFilesToTarget.cmake)
include(cmake/emscripten/enableEmscriptenMT.cmake)
include(cmake/emscripten/enableHTMLOutput.cmake)

include(GNUInstallDirs)
include(ExternalProject)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_BINDIR}")
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_BINARY_DIR}/${CMAKE_INSTALL_LIBDIR}")

if(CMAKE_SYSTEM_NAME MATCHES "Emscripten")
  set(AW_OS_EMSCRIPTEN 1)
elseif(CMAKE_SYSTEM_NAME MATCHES "Android")
  set(AW_OS_ANDROID 1)
else()
  set(AW_OS_DESKTOP 1)
endif()

if (MSVC)
  set(CMAKE_DEBUG_POSTFIX "d")
endif()

set(CMAKE_POSITION_INDEPENDENT_CODE ON)

set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)

option(AW_TESTS "Build and run tests" OFF)
option(AW_BUILD_ENGINE "Build engine" ON)
option(AW_BUILD_DEPENDENCIES "Build dependencies for current platform" OFF)

message(STATUS "Build depdencies: ${AW_BUILD_DEPENDENCIES}")

#Check if dependencies are already build
if(AW_BUILD_DEPENDENCIES)
  include(cmake/buildDependencies.cmake)
endif()

# Encourage user to specify a build type (e.g. Release, Debug, etc.), otherwise set it to Release.
if(NOT CMAKE_CONFIGURATION_TYPES)
    if(NOT CMAKE_BUILD_TYPE)
        message(STATUS "Setting build type to 'Release' as none was specified.")
        set_property(CACHE CMAKE_BUILD_TYPE PROPERTY VALUE "Release")
    endif()
endif()

set(AW_INCLUDE_DIR
  $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
  $<INSTALL_INTERFACE:include>
)

# Use our precompiled dependencies!
set(CMAKE_PREFIX_PATH ${CMAKE_CURRENT_SOURCE_DIR}/dependencies/bin/${CMAKE_SYSTEM_NAME})

# Define awUtil
add_library(awUtil src/aw/util/log/log.cpp)
add_subdirectory(include/aw/util)
add_subdirectory(src/aw/util)
target_include_directories(awUtil PUBLIC ${AW_INCLUDE_DIR})
include(cmake/addUtilDependencies.cmake)

add_library(awOpenGL src/aw/opengl)
add_subdirectory(include/aw/opengl)
add_subdirectory(src/aw/opengl)
target_include_directories(awOpenGL PUBLIC ${AW_INCLUDE_DIR})
include(cmake/addOpenGLDependencies.cmake)

if(AW_BUILD_ENGINE)
  add_library(awEngine src/aw/engine/engine.cpp)
  add_subdirectory(include/aw/engine/)
  add_subdirectory(src/aw/engine/)
  target_include_directories(awEngine PUBLIC ${AW_INCLUDE_DIR})
  include(cmake/addEngineDependencies.cmake)
endif()

if(AW_TESTS)
  enable_testing()
  add_subdirectory(test)
endif()
