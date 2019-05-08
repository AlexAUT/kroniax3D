project(awTest)

set(TEST_FILES
  ${CMAKE_CURRENT_SOURCE_DIR}/testMain.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/util/containers/testRingBuffer.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/util/message/testBus.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/util/file/testInputOutput.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/util/file/testPath.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/util/file/testPathRegistry.cpp
)

add_executable(${PROJECT_NAME} ${TEST_FILES})

find_package(Catch2 REQUIRED)
target_link_libraries(${PROJECT_NAME} PUBLIC Catch2::Catch2 awEngine awUtil)

include(cmake/Catch.cmake)
catch_discover_tests(${PROJECT_NAME})

