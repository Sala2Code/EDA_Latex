SRC := $(filter-out src/main.c test.c, $(wildcard src/*.c))

compile:
	g++ src/main.c $(SRC) -o main

clean:
	rm -f main *.o
