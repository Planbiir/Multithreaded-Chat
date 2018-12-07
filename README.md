# Multithreaded-Chat
##Description
Chats uses sockets and threads. Server keeps listening for new connections, and when a new client arrives, a new thread is created, which receives messages from this client and sends this message to all connected clients.

##Make
```
>$ make
g++ -Wall -g  -c src/server_main.cpp -o obj/server_main.o
g++ -Wall -g  -c src/server.cpp -o obj/server.o
g++ -Wall -g  -c src/client.cpp -o obj/client.o
g++ -Wall -g -pthread -o ./bin/server ./obj/server_main.o  ./obj/server.o ./obj/client.o
g++ -Wall -g  -c src/client_main.cpp -o obj/client_main.o
g++ -Wall -g -pthread -o ./bin/client ./obj/client_main.o  ./obj/client.o

```
Run server

```
>$ ./bin/server
Server start

```
Run client

```
>$ ./bin/client
Please enter your nickname: 

```
