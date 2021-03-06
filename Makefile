# CXX=g++
CXX=clang++
CXXFLAGS= -std=c++14 -O2
WARNINGS= -Wall -Wpedantic #-Weverything -Wno-c++98-compat
LIBRARY=

CXXFLAGS+=${WARNINGS}

.PHONY: all
all: ncg++


ncg++: basic_maths.o gamma_matrix.o clifford_algebra.o odd_clifford_group.o main.o
	${CXX} -o $@ $^ ${CXXFLAGS} ${LIBRARY}



%.o: %.cpp
	${CXX} -c ${CXXFLAGS} $< -o $@


clean:
	rm -f *.o
	rm -f ncg++
