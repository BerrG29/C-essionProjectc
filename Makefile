CC = cc
CFLAGS = -g -W
RM = rm -f
all: mongoose network

mongoose:
	$(CC) -c ./thirdParty/mongoose/mongoose.c -o ./bin/mongoose.o
network:
	$(CC) -c storage.c -o ./bin/storage.o $(CFLAGS)
	$(CC) -o ./bin/lineModule lineModule.c $(CFLAGS) ./bin/*.o
	$(CC) -o ./bin/client client.c $(CFLAGS) ./bin/mongoose.o

clean:
	$(RM) ./bin/*
