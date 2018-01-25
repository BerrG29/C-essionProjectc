CC = cc
CFLAGS = -g -W
ALLFLAGS = -Wall
STD = --std=c99
RM = rm -Rf
all: mongoose network appli affichage traitement

mongoose:
	$(CC) -c ./thirdParty/mongoose/mongoose.c -o ./bin/mongoose.o

network:
	$(CC) $(STD) -c ./src/storage.c -o ./bin/storage.o $(CFLAGS) 
	$(CC) $(STD) -c ./src/client.c -o ./bin/client.o $(CFLAGS) ./bin/mongoose.o
	$(CC) $(STD) -o ./bin/lineModule ./src/lineModule.c $(CFLAGS) ./bin/mongoose.o ./bin/storage.o

appli:
	$(CC) -o ./bin/appli.o -c ./src/appli.c $(CFLAGS)
	$(CC) -c ./src/crypto.c -o ./bin/crypto.o $(CFLAGS) -lcrypt
	$(CC) -c ./src/checkPass.c -o ./bin/checkPass.o $(CFLAGS) -lcrypt

affichage:
	#$(CC) -o ./bin/projet ./src/projet_c.c $(CFLAGS)
	$(CC) -c ./src/couleur.c -o ./bin/couleur.o $(CFLAGS)
	$(CC) -c ./src/echequier.c -o ./bin/echequier.o $(CFLAGS)



#traitement: 
	#$(CC) $(STD) $(CFLAGS) $(ALLFLAGS) ./src/traitement.c -o ./bin/traitement ./bin/checkPass.o ./bin/crypto.o ./bin/dialPostTrait.o ./bin/appli.o  ./bin/couleur.o ./bin/echequier.o ./bin/client.o ./bin/mongoose.o -lcrypt
	#$(CC) $(STD) $(CFLAGS) $(ALLFLAGS) ./src/traitement.c -o ./bin/traitement ./bin/dialPostTrait.o ./bin/appli.o ./bin/checkPass.o ./bin/crypto.o -lcrypt ./bin/couleur.o ./bin/echequier.o

traitement:
	$(CC) $(STD) -c ./src/dialPostTrait.c -o ./bin/dialPostTrait.o $(CFLAGS)
	$(CC) $(STD) $(CFLAGS) $(ALLFLAGS) ./src/traitement.c -o ./bin/traitement ./bin/mongoose.o ./bin/client.o ./bin/dialPostTrait.o ./bin/appli.o ./bin/checkPass.o ./bin/crypto.o ./bin/couleur.o ./bin/echequier.o -lcrypt

clean:
	$(RM) ./bin/*
