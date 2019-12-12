.PHONY: all clean

CPP = g++
CPPFLAGS = -std=c++14 -O2

all: out clean

out: main.cpp
	${CPP} ${CPPFLAGS} \
	-o out main.cpp

clean:
	rm -f *.o
