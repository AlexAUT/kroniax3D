# glm
if(AW_OS_EMSCRIPTEN OR AW_OS_ANDROID)
  set(glm_DIR ${CMAKE_PREFIX_PATH}/lib/cmake/glm)
endif()
find_package(glm "0.9.9" EXACT REQUIRED PATH_SUFFIXES "${CMAKE_PREFIX_PATH}")

# FMT
if(AW_OS_EMSCRIPTEN)
  set(fmt_DIR ${CMAKE_PREFIX_PATH}/lib/cmake/fmt)
elseif(AW_OS_ANDROID)
  set(fmt_DIR ${CMAKE_PREFIX_PATH}/lib/${ANDROID_ABI}/cmake/fmt)
endif()
find_package(fmt REQUIRED)
find_package(cereal REQUIRED)

find_package(Threads REQUIRED)

target_link_libraries(awUtil PUBLIC glm fmt::fmt cereal ${CMAKE_THREAD_LIBS_INIT})

enableEmscriptenMT(awUtil)
