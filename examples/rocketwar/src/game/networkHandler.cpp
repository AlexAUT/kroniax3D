#include "networkHandler.hpp"

#include "basicState.hpp"

#include <aw/util/math/vector.hpp>
#include <aw/util/types.hpp>

#include "shared/gameMessages.hpp"
#include "shared/packetSerializations.hpp"

#include <SFML/Network/IpAddress.hpp>
#include <SFML/Network/Packet.hpp>

#include <iostream>

NetworkHandler::NetworkHandler(BasicState& gameState, std::string serverAddress, int port) :
    mGameState(gameState),
    mServerAddress{serverAddress},
    mPort{port}
{
  mNetClient.connect(mServerAddress, mPort);
}

NetworkHandler::~NetworkHandler() {}

void NetworkHandler::connect() {}

void NetworkHandler::update(float dt)
{
  mNetClient.update(dt);

  /*
  sf::IpAddress serverIP;
  unsigned short serverPort;
  auto status = mSocket.receive(mReceiveBuffer, serverIP, serverPort);

  if (status != sf::UdpSocket::Status::Done)
    return;

  // TODO: maybe check if input came from server?

  ServerMessages type;
  mReceiveBuffer >> type;

  switch (type)
  {
  case ServerMessages::ClientConnected:
    onClientConnected(unzip<ClientConnected>(mReceiveBuffer));
  }
  */
}

void NetworkHandler::tryToConnect() {}

void NetworkHandler::send()
{
  // mSocket.send(mSendBuffer, mServerAddress, mPort);
}

void NetworkHandler::onClientConnected(ClientConnected message)
{
  std::cout << "Received message: " << message.id << std::endl;
}
