SHELL  = /bin/bash
CC     = g++
CFLAGS = -Wall -W -std=c99 -pedantic
LIBS   =

swap.out: swap.o complexe.o td1.o 
	$(CC) -o swap.out td1.o swap.o complexe.o
td1.o: td1.cpp
	$(CC) -c td1.cpp
swap.o: swap.cpp swap.h
	$(CC) -c swap.cpp
complexe.o: complexe.cpp complexe.h
	$(CC) -c complexe.cpp
clean ::
	\rm -f *.o core && rm -f *.out core

distclean :: clean
	\rm -f *% $(EXECS) $(EXECSUTIL) $(EXECSTIMER)
