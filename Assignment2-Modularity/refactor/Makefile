.PHONY: all clean

CPP = g++
CPPFLAGS = -std=c++11 -O2

all: wave1d

wave1d: main.o
	${CPP} -o wave1d main.o

main.o: io.hpp
	${CPP} ${CPPFLAGS} -c -o main.o main.cpp

clean:
	rm -f *.o
