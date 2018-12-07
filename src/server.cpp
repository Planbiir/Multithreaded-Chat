#include "server.h"

using namespace std;

//Static member
vector<Client> Server::clients;
mutex mutex_;

Server::Server() {

    //Init serverSock
    serverSock = socket(AF_INET, SOCK_STREAM, 0);
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_addr.s_addr = INADDR_ANY;
    serverAddr.sin_port = htons(PORT);

    if(bind(serverSock, (struct sockaddr *) &serverAddr, sizeof(sockaddr_in)) < 0)
        cerr << "Failed to bind";
    //Start listening
    listen(serverSock, SOMAXCONN);//Set the backlog to a maximum reasonable value
}

void Server::AcceptAndDispatch() {
    Client *client;
    socklen_t addrLen = sizeof(sockaddr_in);

    for(;;) {

        client = new Client();

        //Blocks at accept(), until a new connection comes.
        client->SetSock(accept(serverSock, (struct sockaddr *) &clientAddr, &addrLen));

        if(client->GetSock() < 0) {
            cerr << "Error on accept";
        }
        //Create a new thread to handle the new client.
        else {
            thread new_thread(Server::HandleClient, client);
            new_thread.detach();
        }
    }
}

void *Server::HandleClient(Client *client) {

    char buffer[SIZE_OF_BUFFER];
    char message[SIZE_OF_BUFFER];
    //State of recv() function
    int stateRecv;

    //Critical section. Add new client.
    mutex_.lock();

    //Making ID for Client
    client->SetId(Server::clients.size());

    cout << "New user with ID: " << client->GetID() << endl;
    Server::clients.push_back(*client);

    //Set client nickname
    memset(buffer, 0, sizeof(buffer));

    if(recv(client->GetSock(), buffer, sizeof(buffer), 0) < 0)
        cerr << "Error while receiving message from client: ";
    client->SetName(buffer);
    cout << "User with ID: " << client->GetID() << " set new nickname: " << client->GetName() << endl;

    mutex_.unlock();

    for(;;) {
        memset(buffer, 0, sizeof(buffer));

        stateRecv = recv(client->GetSock(), buffer, sizeof(buffer), 0);

        //Client disconnected?
        if(stateRecv == 0) {
            cout << "User with ID: " << client->GetID() << " diconnected" << endl;
            close(client->GetSock());
            //Remove client fron vector.
            Server::RemoveClient(client);
            break;
        }
        else if(stateRecv < 0) {
            cerr << "Error while receiving message from client: " << client->GetName() << endl;
        }
        else {
            //Message received. Send message to all clients.
            memset(message, 0, sizeof(message));
            //Who send:>> message
            strcat(message, client->GetName());
            strcat(message, ":>> ");
            strcat(message, buffer);

            cout << client->GetName() << " send message :>> " << buffer << endl;
            Server::SendToAll(message);
        }
    }
    //End thread
    return NULL;
}

void Server::SendToAll(char *message) {

    mutex_.lock();

    for(size_t i=0; i<Server::clients.size(); i++) {
        if(send(Server::clients[i].GetSock(), message, strlen(message), 0) < 0) {
            cout << "Failed to send message";
        }
    }
    mutex_.unlock();
}

void Server::RemoveClient(Client *client) {
    int index = -1;

    mutex_.lock();
    //Critical section. Remove client.
    for(uint i=0; i<Server::clients.size(); i++) {
        if((Server::clients[i].GetID()) == client->GetID()) index = (int)i;
    }
    //Remove client fron vector.
    if(index != -1) {
        Server::clients.erase(Server::clients.begin() + index);
    }
    else {
        cout << "Failed to remove client from vector";
    }
    mutex_.unlock();
}
