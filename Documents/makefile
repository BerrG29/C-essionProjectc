CC = cc
CFLAGS = -g 
RM = rm -f
all: test basic bourrin

basic:
    $(CC) -o forceMe forceMe.c $(CFLAGS) -lcrypto -lssl

bourrin:
    $(CC) -o jackTheBourrin jackTheBourrin.c $(CFLAGS) -lcrypto -lssl

test:
    $(CC) -o test test.c $(CFLAGS) -lcrypto -lssl

clean:
    $(RM) ./forceMe
    $(RM) ./jackTheBourrin
    $(RM) ./dictionary
    $(RM) ./test

