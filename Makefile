CC = cc
CFLAGS = -g -W
ALLFLAGS = -Wall
RM = rm -f
all: appli mongoose network traitement

appli:
	$(CC) -c ./src/appli.c -o ./bin/appli.o $(CFLAGS)

mongoose:
	$(CC) -c ./thirdParty/mongoose/mongoose.c -o ./bin/mongoose.o

network:
	$(CC) -c ./src/storage.c -o ./bin/storage.o $(CFLAGS)
	$(CC) --std=c99 -c ./src/client.c -o ./bin/client.o $(CFLAGS) ./bin/mongoose.o
	$(CC) --std=c99 -o ./bin/lineModule ./src/lineModule.c $(CFLAGS) ./bin/*.o

traitement:
	$(CC) --std=c99 -c ./src/dialPostTrait.c -o ./bin/dialPostTrait.o $(CFLAGS)
	#$(CC) --std=c99 $(CFLAGS) $(ALLFLAGS) ./src/traitement.c -o ./bin/traitement ./bin/client.o ./bin/mongoose.o
	$(CC) --std=c99 $(CFLAGS) $(ALLFLAGS) ./src/traitement.c -o ./bin/traitement ./bin/dialPostTrait.o ./bin/appli.o

clean:
	$(RM) ./bin/*
