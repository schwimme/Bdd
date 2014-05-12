CC=gcc 
FLAGS=-std=c99 -Wall -Wextra -pedantic
OUTPUT=main
OBJ= labels.o node.o errors.o manager.o bdd.o
OBJ-MAKE=labels node errors manager bdd


all: 
	$(CC) $(FLAGS) $(OBJ) main.c -o $(OUTPUT)

obj:$(OBJ-MAKE)
	make

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
	rm -f *.o $(OUTPUT) $(OUTPUT)-prof gmon.out

pack:
	tar cvzf xtrosk00.tar.gz *.c *.h makefile

prof: FLAGS=-std=c99 -Wall -Wextra -pedantic  -g3 -pg
prof: $(OBJ-MAKE)
	$(CC) $(FLAGS) -o $(OUTPUT)-prof $(OBJ) main.c
	./$(OUTPUT)-prof
