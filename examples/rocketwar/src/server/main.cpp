#include "server.hpp"

const int PORT = 14441;

int main()
{
  return 0;
  Server server{PORT};

  server.run();

  return 0;
}
