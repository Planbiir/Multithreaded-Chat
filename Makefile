CFLAGS=-Wall -g 
LDFLAGS=-Wall -g -pthread

COMPILE=g++ $(CFLAGS) -c
LINK=g++ $(LDFLAGS) -o

SRCDIR=./src
OBJDIR=./obj
#OBJ=$(patsubst $(SRCDIR)/%.cpp,$(OBJDIR)/%.o,$(wildcard $(SRCDIR)/*.cpp))
OBJ=$(OBJDIR)/server_main.o  $(OBJDIR)/server.o $(OBJDIR)/client.o
OBJ1=$(OBJDIR)/client_main.o  $(OBJDIR)/client.o
BINDIR=./bin
BIN=$(BINDIR)/server
BIN1=$(BINDIR)/client

all: $(BIN) $(BIN1)

$(BIN): $(OBJ)
	$(LINK) $(BIN) $(OBJ)

$(BIN1): $(OBJ1)
	$(LINK) $(BIN1) $(OBJ1)

$(OBJDIR)/%.o:	$(SRCDIR)/%.cpp
	$(COMPILE) $< -o $@

clean:
	rm -f $(OBJ) $(BIN) $(OBJ1) $(BIN1)

