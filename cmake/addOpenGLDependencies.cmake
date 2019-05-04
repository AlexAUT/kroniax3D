cmake_policy(SET CMP0072 NEW)
find_package(OpenGL)

target_link_libraries(awOpenGL PUBLIC OpenGL::GL)
