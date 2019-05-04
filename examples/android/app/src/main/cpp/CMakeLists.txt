# For more information about using CMake with Android Studio, read the
# documentation: https://d.android.com/studio/projects/add-native-code.html

# Sets the minimum version of CMake required to build the native library.

cmake_minimum_required(VERSION 3.4.1)

# Creates and names a library, sets it as either STATIC
# or SHARED, and provides the relative paths to its source code.
# You can define multiple libraries, and CMake builds them for you.
# Gradle automatically packages shared libraries with your APK.

set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_STANDARD 17)


set(AW_TESTS OFF CACHE BOOL "Disable tests" FORCE)
set(AW_BUILD_DEPENDENCIES ON CACHE BOOL "Build engine dependencies" FORCE)

add_subdirectory(/home/alex/Documents/git/awEngine/ "awEngine")

add_library( # Sets the name of the library.
             native-lib

             # Sets the library as a shared library.
             SHARED

             # Provides a relative path to your source file(s).
             ../../../../../basic/main.cpp )

# Searches for a specified prebuilt library and stores the path as a
# variable. Because CMake includes system libraries in the search path by
# default, you only need to specify the name of the public NDK library
# you want to add. CMake verifies that the library exists before
# completing its build.

find_library( # Sets the name of the path variable.
              log-lib

              # Specifies the name of the NDK library that
              # you want CMake to locate.
              log )

# Specifies libraries CMake should link to your target library. You
# can link multiple libraries, such as libraries you define in this
# build script, prebuilt third-party libraries, or system libraries.

set(SFML_DIR ${ANDROID_NDK}/sources/third_party/sfml/lib/${ANDROID_ABI}/cmake/SFML)
find_package(SFML REQUIRED COMPONENTS window system)


target_link_libraries( # Specifies the target library.
                       native-lib

                       # Links the target library to the log library
                       # included in the NDK.
                       ${log-lib}
                       awUtil
                       awEngine
                       android
                       EGL
        GLESv1_CM

        -Wl,--whole-archive sfml-main -Wl,--no-whole-archive

        )