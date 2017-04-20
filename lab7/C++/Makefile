CC = g++
CFLAGS = -g -Wall -O2 -std=c++11
SRC = $(wildcard *.cpp)
OBJ = $(patsubst %.cpp, %.o, $(SRC))
BIN = p1 p2

.PHONY: all clean

all: $(BIN)

build: lab7

build-p1: Graph.o Node.o p1.o
	$(CC) $(CFLAGS) Graph.o Node.o p1.o Utils.h -o p1
  
run-p1: p1
	./p1; cat test01.out

build-p2: Graph.o Node.o p2.o
	$(CC) $(CFLAGS) Graph.o Node.o p2.o Utils.h -o p2

run-p2: p2
	./p2; cat test02.out

p1.o: p1.cpp
	$(CC) $(CFLAGS) -c p1.cpp

p2.o: p2.cpp
	$(CC) $(CFLAGS) -c p2.cpp

main.o: main.cpp
	$(CC) $(CFLAGS) -c main.cpp
	
Graph.o: Graph.cpp
	$(CC) $(CFLAGS) -c Graph.cpp

Node.o: Node.cpp
	$(CC) $(CFLAGS) -c Node.cpp
	
clean:
	rm -f $(OBJ)
	rm -f $(BIN)
	rm -f *~
	rm -f *.out
