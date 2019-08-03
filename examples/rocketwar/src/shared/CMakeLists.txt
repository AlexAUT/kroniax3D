set(SOURCE_LIST
  ${CMAKE_CURRENT_SOURCE_DIR}/gameMessages.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/gameMessages.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/missle.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/missle.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ship.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/ship.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/shipController.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/shipController.cpp

  ${CMAKE_CURRENT_SOURCE_DIR}/network/channel.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/network/channel.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/network/client.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/network/client.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/network/connection.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/network/connection.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/network/host.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/network/host.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/network/incommingPacket.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/network/incommingPacket.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/network/outgoingPacket.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/network/outgoingPacket.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/network/packet.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/network/packet.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/network/protocol.hpp
  ${CMAKE_CURRENT_SOURCE_DIR}/network/protocol.cpp
  ${CMAKE_CURRENT_SOURCE_DIR}/network/types.hpp
)

target_sources(${PROJECT_NAME}_game PRIVATE ${SOURCE_LIST})
target_sources(${PROJECT_NAME}_server PRIVATE ${SOURCE_LIST})
