SHELL  = /bin/bash
CC     = g++
CFLAGS = -Wall -W -std=c99 -pedantic
LIBS   =

vector.out: vector.o complexe.o td2.o vector15.o
	$(CC) -o  vector.out td2.o complexe.o vector.o vector15.o 
td2.o: td2.cpp
	$(CC) -c td2.cpp
complexe.o: complexe.cpp complexe.h
	$(CC) -c complexe.cpp
vector.o: vector.h vector.cpp
	$(CC) -c vector.cpp
vector15.o: vector15.h vector15.cpp
	$(CC) -c vector15.cpp
clean ::
	\rm -f *.o core && rm -f *.out core

distclean :: clean
	\rm -f *% $(EXECS) $(EXECSUTIL) $(EXECSTIMER)
