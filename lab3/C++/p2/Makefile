CC=g++
CXXFLAGS=-Wall -g
all: carti

carti: carti.cpp
	$(CC) $(CXXFLAGS) -o $@ $^

run:
	./carti && cat carti.out

clean:
	rm carti


