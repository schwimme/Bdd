CC=gcc 
FLAGS=-std=c99 -Wall -Wextra -pedantic
OUTPUT=main
OBJ= cache.o labels.o node.o errors.o manager.o bdd.o
OBJ-MAKE=cache labels node errors manager bdd


all: obj

obj:$(OBJ-MAKE)

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
  
cache:cache.c cache.h
	$(CC) $(FLAGS) -c cache.c

meas:
	$(CC) $(FLAGS) -c measurement.c

app:
	$(CC) $(FLAGS) $(OBJ) main.c -o $(OUTPUT)

run:
	./$(OUTPUT)
t-init:
	$(CC) $(FLAGS) $(OBJ) measurement.o tests/t-init.c -o t-init
	./t-init
t-simplyf:
	$(CC) $(FLAGS) $(OBJ) measurement.o tests/t-simplyf.c -o t-simplyf
	./t-simplyf
t-bigf:
	$(CC) $(FLAGS) $(OBJ) measurement.o tests/t-bigf.c -o t-bigf
	./t-bigf
m-init:
	$(CC) $(FLAGS) $(OBJ) tests/t-init.c -o m-init
	valgrind ./m-init
m-simplyf:
	$(CC) $(FLAGS) $(OBJ) tests/m-simplyf.c -o m-simplyf
	valgrind ./m-simplyf
m-bigf:
	$(CC) $(FLAGS) $(OBJ) tests/m-bigf.c -o m-bigf
	valgrind ./m-bigf


clean:
	rm -f *.o $(OUTPUT) $(OUTPUT)-prof gmon.out t-* m-* xtrosk00.tar.gz

pack: clean
	tar cvzf xtrosk00.tar.gz *

prof: FLAGS=-std=c99 -Wall -Wextra -pedantic  -g3 -pg
prof: $(OBJ-MAKE)
	$(CC) $(FLAGS) -o $(OUTPUT)-prof $(OBJ) measurement.o main.c

