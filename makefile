CC = cc
CFLAGS = -g 
RM = rm -f
all: interface reseau traitement

interface:
    $(CC) -o forceMe forceMe.c $(CFLAGS) -lcrypto -lssl

reseau:
    $(CC) -o jackTheBourrin jackTheBourrin.c $(CFLAGS) -lcrypto -lssl

traitement:
    $(CC) -o test test.c $(CFLAGS) -lcrypto -lssl

clean:
    $(RM) ./forceMe

