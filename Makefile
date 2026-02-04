CC := gcc
CFLAGS := -W -Wall -Wshadow -pedantic -g

all: main

main: funcoes.o main_trabalho.o
	$(CC) $(CFLAGS) funcoes.o main_trabalho.o -o bin_main

funcoes.o: funcoes.c funcoes.h struct_func.h
	$(CC) $(CFLAGS) -c funcoes.c

main_trabalho.o: main_trabalho.c funcoes.h
	$(CC) $(CFLAGS) -c main_trabalho.c

run: all
	./bin_main

clean:
	rm -f *.o bin_main