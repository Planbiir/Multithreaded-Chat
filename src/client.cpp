#include "client.h"

using namespace std;

Client::Client() {
    this->name = new char[MAX_NAME_LENGHT];
}
//Another constructor for client side.
Client::Client(int option) {
    name = new char[MAX_NAME_LENGHT];

    std::cout << "Please enter your nickname: ";
    std::cin >> name;

    sock = socket(AF_INET, SOCK_STREAM, 0);

    addr.sin_family = AF_INET;
    addr.sin_addr.s_addr = INADDR_ANY;
    addr.sin_port = htons(PORT);
    addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);//"127.0.0.1"

    if(connect(sock, (struct sockaddr *) &addr, sizeof(sockaddr_in)) < 0)
        cerr << "Failed to connect" << endl;

}
void Client::SetName(char *name) {
    strcpy(this->name, name);
}
void Client::SetId(int id) {
    this->id = id;
}
void Client::SetSock(int sock) {
    this->sock = sock;
}
char* Client::GetName() {
    return this->name;
}
int Client::GetID() {
    return this->id;
}
int Client::GetSock() {
    return this->sock;
}
