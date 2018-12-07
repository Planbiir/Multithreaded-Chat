#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <string.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <thread>

#include "client.h"

using namespace std;

#define PORT 8080
#define SIZE_OF_BUFFER 256
#define MAX_NAME_LENGHT 20

static void* SendingMessages(Client *client) {
    char message[SIZE_OF_BUFFER];
    string inputStr;
    for(;;) {
        memset(message, 0, sizeof(message));

        cin >> inputStr;
        strcpy(message,inputStr.c_str());

        if(send(client->GetSock(), message, sizeof(message), 0) < 0)
            cerr << "Failed to send message" << endl;
    }
    return NULL;
}

int main()
{
    //1-option to start constructor for client side
    Client *client = new Client(1);

    char buffer[SIZE_OF_BUFFER];
    char message[SIZE_OF_BUFFER];
    //State of recv() function
    int stateRecv;

    //Send Server message with the client nickname
    strcat(message,"_");
    strcat(message,client->GetName());
    if(send(client->GetSock(), message, sizeof(message), 0) < 0)
        cerr << "Failed to send message" << endl;

    //Create a new thread to sending client messages.
    thread thread_sending(SendingMessages,client);
    thread_sending.detach();

    for(;;)
    {
        memset(buffer, 0, sizeof(buffer));
        stateRecv = recv(client->GetSock(), buffer, sizeof(buffer), 0);

        if(stateRecv == 0) {
            cout << "Server crashed" << endl;
            close(client->GetSock());

            break;
        }
        else if(stateRecv < 0) {
            cerr << "Error while receiving message from server" << endl;
        }
        else {
            //Message received.
            cout << buffer << endl;
        }
    }
    close(client->GetSock());

    return 0;
}