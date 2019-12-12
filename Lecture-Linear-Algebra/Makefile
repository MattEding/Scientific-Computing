.PHONY: all clean

CPP = g++
CPPFLAGS = -std=c++11 -O2
BLAS = -I ${BLAS_INC} -L ${BLAS_LIB} -lopenblas

all: dscal dgemm dgesv clean

dscal: dscal.cpp io.hpp
	${CPP} ${CPPFLAGS} \
	${BLAS} \
	-o dscal dscal.cpp

dgemm: dgemm.cpp io.hpp
	${CPP} ${CPPFLAGS} \
	${BLAS} \
	-o dgemm dgemm.cpp

dgesv: dgesv.cpp io.hpp
	${CPP} ${CPPFLAGS} \
	${BLAS} \
	-o dgesv dgesv.cpp

clean:
	rm -f *.o
