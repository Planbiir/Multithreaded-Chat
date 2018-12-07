# Multithreaded-Chat

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
>$ ./bin/server
Server start

```
