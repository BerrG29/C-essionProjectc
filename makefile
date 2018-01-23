CC = cc
CFLAGS = -g 
RM = rm -f
all: interface reseau traitement

interface:
	$(CC) -o rulesDef rulesDef.c $(CFLAGS)

appli:
	$(CC) -o appli appli.c $(CFLAGS)

reseau:
	
traitement:

clean:
	$(RM) appli
