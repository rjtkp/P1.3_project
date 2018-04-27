# Makefile for BST exam

## LOCATIONS
SHELL=/bin/bash
ROOTDIR=..
SRCDIR=$(ROOTDIR)/src
HEADDIR=$(ROOTDIR)/include
EXEDIR=$(ROOTDIR)
#ESDIR=$(ROOTDIR)/examples
DOXYDIR=$(ROOTDIR)/Doxygen
VPATH=$(SRCDIR)

## PARAMETERS
TOL=0.000001 # needed to compare two doubles


## COMPILING
CXX= g++
CFLAGS= -I $(HEADDIR) -O3  -Wall -Wextra -D TOL=$(TOL)
DBFLAGS= -g -ggdb
LFLAGS= -std=c++11

## EXE OBJECTS SOURCES HEADERS
EXE=$(ROOTDIR)/bst.x
SRC=$(SRCDIR)/bst_main.cc
OBJ=$(SRC:%.cc=%.o)
HEAD=$(wildcard $(HEADDIR)/*.h)


compile: $(EXE)

$(EXE): $(OBJ)
	$(CXX) $^ -o $@ $(CFLAGS) $(DBFLAGS) $(LFLAGS)

$(SRCDIR)/%.o: $(SRCDIR)/%.cc $(HEAD)
	$(CXX) -c $< -o $@ $(CFLAGS) $(DBFLAGS) $(LFLAGS)

#$(SRCDIR)/bst_main.o: ./include/ap_error.h ./include/bst.h

clean:
	rm -rf $(SRCDIR)/*.o $(ROOTDIR)/*.o $(SRCDIR)/*~ $(HEADDIR)/*~ $(EXE) $(ROOTDIR)/bst_doc/

doc: $(DOXYDIR)/doxy.in
	doxygen $^

#check:./bst.x
#	./bst.x < examples/es1.inp

.PHONY: clean
