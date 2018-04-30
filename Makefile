# -*- Makefile -*-
SHELL=/bin/bash
ROOTDIR=.
ESDIR=$(ROOTDIR)/examples
EXE=./bst.x

PYTHON=python3.4 # python 3.4 (on ulysses)

compile:
	$(MAKE) $(MFLAGS) -C src compile

test1:
	$(MAKE) $(MFLAGS) -C src compile
	$(EXE) < $(ESDIR)/es1.inp
test1v:
	$(MAKE) $(MFLAGS) -C src compile
	valgrind $(EXE) < $(ESDIR)/es1.inp

test2:
	$(MAKE) $(MFLAGS) -C src compile
	$(EXE) < $(ESDIR)/es2.inp
test2v:
	$(MAKE) $(MFLAGS) -C src compile
	valgrind $(EXE) < $(ESDIR)/es2.inp

test3:
	$(MAKE) $(MFLAGS) -C src compile
	$(EXE) < $(ESDIR)/es3.inp
test3v:
	$(MAKE) $(MFLAGS) -C src compile
	valgrind $(EXE) < $(ESDIR)/es3.inp

test4:
	$(MAKE) $(MFLAGS) -C src compile
	$(EXE) < $(ESDIR)/es4.inp
test4v:
	$(MAKE) $(MFLAGS) -C src compile
	$(EXE) < $(ESDIR)/es4.inp

test5:
	$(MAKE) $(MFLAGS) -C src compile
	$(EXE) < $(ESDIR)/es5.inp
test5v:
	$(MAKE) $(MFLAGS) -C src compile
	valgrind $(EXE) < $(ESDIR)/es5.inp

test6:
	$(MAKE) $(MFLAGS) -C src compile
	$(EXE) < $(ESDIR)/es6.inp
test6v:
	$(MAKE) $(MFLAGS) -C src compile
	valgrind $(EXE) < $(ESDIR)/es6.inp

test7:
	$(MAKE) $(MFLAGS) -C src compile
	$(EXE) < $(ESDIR)/es7.inp
test7v:
	$(MAKE) $(MFLAGS) -C src compile
	valgrind $(EXE) < $(ESDIR)/es7.inp


test_bal:
	$(MAKE) $(MFLAGS) -C src compile
	$(EXE) < $(ESDIR)/balanced1.inp
test_balv:
	$(MAKE) $(MFLAGS) -C src compile
	valgrind $(EXE) < $(ESDIR)/balanced1.inp

bst_doc:
	$(MAKE) $(MFLAGS) -C src doc

#part1:
#	$(MAKE) $(MFLAGS) -C src part1

clean:
	$(MAKE) $(MFLAGS) -C src clean
	rm -f ./*~

postcards:
	$(MAKE) $(MFLAGS) -C python postcards


.PHONY: clean default test1 test2 test3 test4 test5 test_bal test1v test2v test3v test4v test5v test_balv doc postcards
