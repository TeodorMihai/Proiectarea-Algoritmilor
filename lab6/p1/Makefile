CXX=g++
CXXFLAGS=-Wall

build: labirint

labirint: labirint.o
	$(CXX) $(CXXFLAGS) -o $@ $^

labirint.o: labirint.cpp

run: labirint
	./labirint

clean:
	rm labirint labirint.o

