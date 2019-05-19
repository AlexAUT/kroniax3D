cmake_minimum_required(VERSION 3.10)

include(ExternalProject)

set(OS_ARGS)

if(CMAKE_SYSTEM_NAME MATCHES "Android")
  set(OS_ARGS
    -DANDROID_PLATFORM=${ANDROID_PLATFORM}
    -DANDROID_NDK=${ANDROID_NDK}
    -DCMAKE_SYSTEM_NAME=${CMAKE_SYSTEM_NAME}
    -DCMAKE_ANDROID_NDK=${CMAKE_ANDROID_NDK}
    -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
    -DANDROID_ABI=${ANDROID_ABI}
  )


endif()

include(cmake/glm.cmake)
include(cmake/fmt.cmake)
include(cmake/cereal.cmake)
include(cmake/sfml.cmake)
include(cmake/assimp.cmake)

if((NOT CMAKE_SYSTEM_NAME MATCHES "Android") AND (NOT CMAKE_SYSTEM_NAME MATCHES "Emscripten"))
  include(cmake/catch2.cmake)
endif()
