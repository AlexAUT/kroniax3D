#include "server.hpp"

const int PORT = 14441;

int main()
{
  Server server;

  server.run(PORT);

  return 0;
}
