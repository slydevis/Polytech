SHELL  = /bin/bash
CC     = g++
CFLAGS = -Wall -W -pedantic -g
LIBS   =

OFILES =  td4.o Displayable.o complexe.o MesExceptions.o VectorException.o vector.o
displayable.out: td4.o Displayable.o complexe.o MesExceptions.o VectorException.o vector.o
	$(CC) -o  displayable.out $(OFILES) $(CFLAGS)
td4.o: td4.cpp
	$(CC) -c td4.cpp $(CFLAGS)
complexe.o: complexe.h complexe.cpp
	$(CC) -c complexe.cpp
vector.o: vector.h vector.cpp
	$(CC) -c vector.cpp
Displayable.o: Displayable.h Displayable.cpp
	$(CC) -c Displayable.cpp
MesExceptions.o: MesExceptions.h MesExceptions.cpp
	$(CC) -c MesExceptions.cpp
VectorException.o: VectorException.h VectorException.cpp
	$(CC) -c VectorException.cpp
PileExceptions.o: PileExceptions.h PileExceptions.cpp
	$(CC) -c PileExceptions.cpp
clean ::
	\rm -f *.o core && rm -f *.out core

distclean :: clean
	\rm -f *% $(EXECS) $(EXECSUTIL) $(EXECSTIMER)
