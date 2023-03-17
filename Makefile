CC = gcc $(CFLAGS)
DEBUG = -g
CFLAGS = $(DEBUG) -Wall -Werror -Wunsafe-loop-optimizations -Wshadow -Wunreachable-code -Wredundant-decls -Wmissing-declarations -Wold-style-definition -Wmissing-prototypes -Wdeclaration-after-statement -Wno-return-local-addr -Wuninitialized

primesMT: primesMT.o
	$(CC) primesMT.o -o primesMT -lm -pthread

primesMT.o: primesMT.c
	$(CC) $(CFLAGS) -c primesMT.c

clean:
	rm -f *.o *.gz *.c~ *.log *.err

all: primesMT


