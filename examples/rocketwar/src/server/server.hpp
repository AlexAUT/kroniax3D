#pragma once

#include "client.hpp"

#include "game.hpp"

#include <memory>
#include <mutex>
#include <vector>

class Server
{
public:
  Server();
  ~Server();

  bool run(int port);

  void onClientDisconnect(Client* client);

private:
  void gameThreadFunc();

private:
  bool mRunning{true};

  std::vector<std::unique_ptr<Client>> mClients;
  std::mutex mClientsLock;

  std::thread mGameThread;

  Game mGame;
};
