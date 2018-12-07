#ifndef _server_h_
#define _server_h_

#include <iostream>
#include <vector>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <mutex>

#include "client.h"

using namespace std;

#define PORT 8080
#define SIZE_OF_BUFFER 256

class Server {

private:
    static vector<Client> clients;

    //Socket
    int serverSock, clientSock;
    struct sockaddr_in serverAddr, clientAddr;

public:
    Server();
    void AcceptAndDispatch();
    static void * HandleClient(Client *client);

private:
    static void SendToAll(char *message);
    static void RemoveClient(Client *client);
};

#endif
