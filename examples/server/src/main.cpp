#include <iostream>
#include <thread>

#include <aw/util/log/consoleSink.hpp>
#include <aw/util/log/log.hpp>
#include <aw/util/log/module.hpp>

#include <SFML/Network/TcpListener.hpp>
#include <SFML/Network/TcpSocket.hpp>

const int PORT = 14441;

bool mRunning = true;

namespace aw::log
{
inline Module serverLogModule("Server");
}

#define LOG_SERVER_F(...)                                                                          \
  aw::log::getDefaultLogger()->log(aw::log::serverLogModule, __FILE__, __LINE__, __func__,         \
                                   aw::log::Level::Fatal, __VA_ARGS__);
#define LOG_SERVER_E(...)                                                                          \
  aw::log::getDefaultLogger()->log(aw::log::serverLogModule, __FILE__, __LINE__, __func__,         \
                                   aw::log::Level::Error, __VA_ARGS__);
#define LOG_SERVER_W(...)                                                                          \
  aw::log::getDefaultLogger()->log(aw::log::serverLogModule, __FILE__, __LINE__, __func__,         \
                                   aw::log::Level::Warning, __VA_ARGS__);
#define LOG_SERVER_D(...)                                                                          \
  aw::log::getDefaultLogger()->log(aw::log::serverLogModule, __FILE__, __LINE__, __func__,         \
                                   aw::log::Level::Debug, __VA_ARGS__);
#define LOG_SERVER_V(...)                                                                          \
  aw::log::getDefaultLogger()->log(aw::log::serverLogModule, __FILE__, __LINE__, __func__,         \
                                   aw::log::Level::Verbose, __VA_ARGS__);

void listenForConnections()
{
  sf::TcpListener listener;
  listener.setBlocking(true);
  listener.listen(PORT);
  LOG_SERVER_V("Listening on PORT {} for new connections", PORT);

  bool mRunning = true;

  while (mRunning)
  {
    sf::TcpSocket socket;
    auto status = listener.accept(socket);

    if (status != sf::Socket::Status::Done)
    {
      LOG_SERVER_D("Client connection failed?");
      continue;
    }

    LOG_SERVER_D("Client connected: {}", socket.getRemoteAddress().toString());

    socket.disconnect();

    mRunning = false;
  }

  listener.close();
}

int main()
{
  auto logger = std::make_shared<aw::log::Logger>();
  logger->addSink(std::make_shared<aw::log::ConsoleSink>());
  aw::log::setDefaultLogger(logger);

  LOG_SERVER_V("Starting server...");

  std::thread connectionListener(listenForConnections);

  if (connectionListener.joinable())
    connectionListener.join();

  return 0;
}
