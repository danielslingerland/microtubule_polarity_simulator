CC=g++
CFLAGS=-I. -O3 -std=gnu++11
DEPS = Cell.h FileWriter.h Microtubule.h Parameters.h RNG.h

%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS)

mtps: main.o Cell.o FileWriter.o Microtubule.o RNG.o
	$(CC) -o mtps main.o Cell.o FileWriter.o Microtubule.o RNG.o 
