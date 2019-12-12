.PHONY: all clean

CPP = g++
CPPFLAGS = -std=c++14 -O2
EIGEN = -I ${EIGEN_INC}

all: out clean

out: main.cpp
	${CPP} ${CPPFLAGS} \
	${EIGEN} \
	-o out main.cpp

clean:
	rm -f *.o
