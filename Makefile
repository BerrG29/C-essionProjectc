CC = cc
CFLAGS = -g -W -Wall
RM = rm -f
all: mongoose network

mongoose:
	$(CC) -c ./thirdParty/mongoose/mongoose.c -o ./bin/mongoose.o
network:
	$(CC) -o ./bin/lineModule lineModule.c $(CFLAGS) ./bin/mongoose.o
	$(CC) -o ./bin/client client.c $(CFLAGS) ./bin/mongoose.o

clean:
	$(RM) ./bin/*
