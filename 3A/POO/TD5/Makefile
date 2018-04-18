SHELL  = /bin/bash
CC     = g++
CFLAGS = -Wall -W -pedantic -g
LIBS   =

OFILES =  td5.o
operator.out: td5.o
	$(CC) -o  operator.out $(OFILES) $(CFLAGS)
td5.o: td5.cpp
	$(CC) -c td5.cpp $(CFLAGS)
clean ::
	\rm -f *.o core && rm -f *.out core

distclean :: clean
	\rm -f *% $(EXECS) $(EXECSUTIL) $(EXECSTIMER)
