#ifndef _client_h_
#define _client_h_

#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string.h>
#include <unistd.h>

#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>
#include <mutex>

#define MAX_NAME_LENGHT 20
#define PORT 8080
#define SIZE_OF_BUFFER 256

using namespace std;

class Client {
private:
    char* name;
    int id;

    //Socket
    int sock;
    struct sockaddr_in addr;

public:
    Client();
    Client(int option);
    void SetName(char *name);
    void SetId(int id);
    void SetSock(int sock);
    char* GetName();
    int GetID();
    int GetSock();
};

#endif
