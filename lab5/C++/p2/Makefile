CFLAGS=-Wall -g
CC=g++

all: p2prun

p2: p2prun.cpp
	$(CC) -std=c++11 $< -o $@ $(CFLAGS)

run: p2prun
	./p2prun

clean:
	rm -rf p2prun
