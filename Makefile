# -*- Makefile -*-                                                                                  
SHELL=/bin/bash
ROOTDIR=.
ESDIR=$(ROOTDIR)/examples
EXE=./bst.x

compile:
	$(MAKE) $(MFLAGS) -C src compile

test1:
	$(MAKE) $(MFLAGS) -C src compile
	$(EXE) < $(ESDIR)/es1.inp
test2:
	$(MAKE) $(MFLAGS) -C src compile
	$(EXE) < $(ESDIR)/es2.inp
test3:
	$(MAKE) $(MFLAGS) -C src compile
	$(EXE) < $(ESDIR)/es3.inp
test4:
	$(MAKE) $(MFLAGS) -C src compile
	$(EXE) < $(ESDIR)/es4.inp
test5:
	$(MAKE) $(MFLAGS) -C src compile
	$(EXE) < $(ESDIR)/es5.inp

test_bal:
	$(MAKE) $(MFLAGS) -C src compile
	$(EXE) < $(ESDIR)/balanced1.inp

bst_doc:
	$(MAKE) $(MFLAGS) -C src doc

#part1:
#	$(MAKE) $(MFLAGS) -C src part1

clean:
	$(MAKE) $(MFLAGS) -C src clean
	rm -f ./*~ 

.PHONY: clean default test1 test2 test3 test4 test5 test_bal doc