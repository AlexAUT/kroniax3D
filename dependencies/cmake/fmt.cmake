set(ANDROID_FLAGS)
if(CMAKE_SYSTEM_NAME MATCHES "Android")
  set(ANDROID_FLAGS
    -DFMT_LIB_DIR=${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}/lib/${ANDROID_ABI}
    -DFMT_CMAKE_DIR=${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}/lib/${ANDROID_ABI}/cmake/fmt
  )
endif()

ExternalProject_Add(fmt_Debug_Static
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source/fmt
  GIT_REPOSITORY "https://github.com/fmtlib/fmt"
  GIT_TAG "8d8ea21c6947b0b5c579878965add8e7b2e8e7cc"
  #DOWNLOAD_COMMAND ""
  UPDATE_COMMAND ""
  CMAKE_ARGS -DCMAKE_BUILD_TYPE=Debug
             -DBUILD_SHARED_LIBS=OFF
             -DFMT_DOC=OFF
             -DFMT_TEST=OFF
             -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}
             -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
             -DCMAKE_POSITION_INDEPENDENT_CODE=ON
             ${OS_ARGS}
             ${ANDROID_FLAGS}
)

ExternalProject_Add(fmt_Release_Static
  PREFIX ${CMAKE_CURRENT_SOURCE_DIR}/build
  DEPENDS fmt_Debug_Static
  DOWNLOAD_COMMAND ""
  SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/source/fmt
  CMAKE_ARGS -DCMAKE_BUILD_TYPE=Release
             -DBUILD_SHARED_LIBS=OFF
             -DFMT_DOC=OFF
             -DFMT_TEST=OFF
             -DCMAKE_INSTALL_PREFIX=${CMAKE_CURRENT_SOURCE_DIR}/bin/${CMAKE_SYSTEM_NAME}
             -DCMAKE_TOOLCHAIN_FILE=${CMAKE_TOOLCHAIN_FILE}
             -DCMAKE_POSITION_INDEPENDENT_CODE=ON
             ${OS_ARGS}
             ${ANDROID_FLAGS}
)
