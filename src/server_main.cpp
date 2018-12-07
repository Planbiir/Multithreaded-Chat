#include <iostream>
#include "server.h"

using namespace std;

int main() {
  cout << "Server start" << endl;

  Server  *s = new Server();

  //Loop
  s->AcceptAndDispatch();

  return 0;
}
