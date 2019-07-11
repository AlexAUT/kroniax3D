set(SOURCE_LIST
  ${CMAKE_CURRENT_SOURCE_DIR}/gameMessages.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/missle.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/missle.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ship.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ship.cpp
  )

target_sources(${PROJECT_NAME}_game PRIVATE ${SOURCE_LIST})
target_sources(${PROJECT_NAME}_server PRIVATE ${SOURCE_LIST})
