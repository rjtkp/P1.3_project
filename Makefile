# Makefile for BST exam
EXE=bst.x
CFLAGS=-I ./include -ggdb -O3  -Wall -Wextra -std=c++11
CXX=g++
VPATH=.#:./src
SRC=bst_main.cc
OBJ=$(SRC:%.cc=%.o)

default: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $^ -o $@ $(CFLAGS)

%.o: %.cc
	$(CXX) -c $< -o $@ $(CFLAGS)

bst_main.o: ./include/ap_error.h ./include/bst.h

clean:
	rm -rf ./src/*.o *.o src/*~ include/*~ *~ html latex a.out $(EXE)

doc: Doxygen/doxy.in
	doxygen $^

check:./bst.x
	./bst.x < examples/es1.inp 

.PHONY: clean doc
