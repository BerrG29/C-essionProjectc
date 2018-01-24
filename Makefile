CC = cc --std=c99
CFLAGS = -g
ALLFLAGS = -Wall
RM = rm -f
all: mongoose network traitement

appli:
	$(CC) -o appli appli.c $(CFLAGS)

mongoose:
	$(CC) -c ./thirdParty/mongoose/mongoose.c -o ./bin/mongoose.o

network:
	$(CC) -c storage.c -o ./bin/storage.o $(CFLAGS)
	$(CC) -o ./bin/lineModule lineModule.c $(CFLAGS) ./bin/*.o
	$(CC) -o ./bin/client client.c $(CFLAGS) ./bin/mongoose.o

traitement:
	$(CC) $(CFLAGS) $(ALLFLAGS) ./src/traitement.c -o ./bin/traitement

clean:
	$(RM) ./bin/*
