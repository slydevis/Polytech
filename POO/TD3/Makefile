SHELL  = /bin/bash
CC     = g++
CFLAGS = -Wall -W -pedantic -g
LIBS   =

pilegen.out: td3.o
	$(CC) -o pilegen.out td3.o $(CFLAGS)
td3.o: td3.cpp PileGen.hxx PileGen.h CNode.h CNode.hxx
	$(CC) -c td3.cpp $(CFLAGS)
#PileGen.o: PileGen.h PileGen.cpp
#	$(CC) -c PileGen.cpp
clean ::
	\rm -f *.o core && rm -f *.out core

distclean :: clean
	\rm -f *% $(EXECS) $(EXECSUTIL) $(EXECSTIMER)
