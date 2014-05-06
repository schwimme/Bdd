CC=gcc 
FLAGS=-std=c99 -Wall -Wextra -pedantic
OUTPUT=main

all: labels node errors manager bdd
	$(CC) $(FLAGS) labels.o node.o errors.o manager.o bdd.o main.c -o $(OUTPUT)


bdd:bdd.c bdd.h
	$(CC) $(FLAGS) -c bdd.c
manager:manager.c manager.h
	$(CC) $(FLAGS) -c manager.c


errors:errors.c errors.h
	$(CC) $(FLAGS) -c errors.c
  
node:node.c node.h
	$(CC) $(FLAGS) -c node.c
 
labels:labels.c labels.h
	$(CC) $(FLAGS) -c labels.c
run:
	clear; 
	valgrind -q --leak-check=full ./$(OUTPUT)
 
clean:
	rm -f *.o $(OUTPUT)

pack:
	tar cvzf xtrosk00.tar.gz *.c *.h makefile
