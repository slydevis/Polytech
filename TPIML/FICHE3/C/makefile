#---------------------------------------------------------------
# Nom du fichier : makefile
# Auteur :
# Objet : Commandes de compilation du programme de gestion de listes
#         doublement chainees d'entiers 
# Pour generer l'executable (listesdc) : tapez "make" ou "make listesdc"
# Pour effacer les fichiers objet et l'executable : tapez "make clean"
#--------------------------------------------------------------------

listesdc: main.o listes.o memoire.o interface.o  
	gcc -Wall -o listesdc main.o listes.o memoire.o interface.o

main.o: main.c listes.h interface.h makefile
	gcc -c -Wall main.c 
listes.o: listes.c interface.h memoire.h listes.h  makefile
	gcc -c -Wall listes.c
memoire.o: memoire.c memoire.h  makefile
	gcc -c -Wall memoire.c
interface.o: interface.c interface.h makefile
	gcc -c -Wall interface.c
clean:	
	rm listesdc *.o
#---------------------fin makefile--------------------------
