# Create build binary dir
file(MAKE_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dependenciesBuild)

# Start cmake for dependecy folder
# For emscripten we need to prepend emcmake
if(AW_OS_EMSCRIPTEN)
  execute_process(
    COMMAND "emcmake" "cmake" ${CMAKE_CURRENT_SOURCE_DIR}/dependencies
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dependenciesBuild
  )
elseif(AW_OS_ANDROID)
  execute_process(
    COMMAND "cmake" ${CMAKE_CURRENT_SOURCE_DIR}/dependencies -DANDROID_PLATFORM=${ANDROID_PLATFORM} -DANDROID_NDK=${ANDROID_NDK} -DCMAKE_SYSTEM_NAME=${CMAKE_SYSTEM_NAME} -DCMAKE_ANDROID_NDK=${CMAKE_ANDROID_NDK} -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE} -DANDROID_ABI=${ANDROID_ABI}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dependenciesBuild
    RESULT_VARIABLE retcode)

  if(NOT "${retcode}" STREQUAL "0")
    message(FATAL_ERROR "Fatal error when configure cmake for deps")
  endif()

else()
  execute_process(
    COMMAND "cmake" ${CMAKE_CURRENT_SOURCE_DIR}/dependencies
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dependenciesBuild
  )
endif()

# Build dependencies
execute_process(
  COMMAND ${PREFIX_COMMAND} ${CMAKE_COMMAND} "--build" "."
  WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dependenciesBuild
)

# For emscripten
#if(CMAKE_SYSTEM_NAME MATCHES "Emscripten")
#  execute_process(
#    COMMAND "emmake" "make"
#    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}/dependenciesBuild
#    RESULT_VARIABLE emake_result
#  )

