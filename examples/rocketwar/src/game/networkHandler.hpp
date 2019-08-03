#pragma once

#include <string>
#include <thread>
#include <vector>

#include <SFML/Network/Packet.hpp>
#include <SFML/Network/UdpSocket.hpp>

#include <aw/util/containers/ringBuffer.hpp>
#include <aw/util/math/vector.hpp>

#include "player.hpp"

#include "shared/gameMessages.hpp"
#include "shared/network/client.hpp"

class BasicState;

class NetworkHandler
{
public:
  NetworkHandler(BasicState& gameState, std::string serverAddress, int port);
  ~NetworkHandler();

  void connect();

  void update(float dt);

  bool connected() const { return mConnected; };

  template <typename Message>
  void send(Message&& msg);

private:
  void send();

  void tryToConnect();

  void onClientConnected(ClientConnected message);

private:
  BasicState& mGameState;

  bool mTryToConnect{true};
  bool mConnected{false};

  std::string mServerAddress;
  int mPort;

  network::Client mNetClient;

  aw::uint64 mClientId{0};
};

