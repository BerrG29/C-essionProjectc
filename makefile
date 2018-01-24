CC = cc
CFLAGS = -g -W
RM = rm -f
all: mongoose network traitement

appli:
	$(CC) -o ./bin/appli ./src/appli.c $(CFLAGS)

mongoose:
	$(CC) -c ./thirdParty/mongoose/mongoose.c -o ./bin/mongoose.o

network:
	$(CC) -c ./src/storage.c -o ./bin/storage.o $(CFLAGS)
	$(CC) --std=c99 -c ./src/client.c -o ./bin/client.o $(CFLAGS) ./bin/mongoose.o
	$(CC) -o ./bin/lineModule ./src/lineModule.c $(CFLAGS) ./bin/*.o

traitement:
	$(CC) --std=c99 $(CFLAGS) ./src/traitement.c -o ./bin/traitement ./bin/client.o ./bin/mongoose.o

clean:
	$(RM) ./bin/*
