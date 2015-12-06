#/*
#-------------------------------------------------------------------
#Nom du fichier : memoire.s (traduction de memoire.c)
#Auteur :
#Objet : Module implantant les fonctions d'allocation et de liberation
#        de la memoire  
#--------------------------------------------------------------------
#*/
##include <stdlib.h>
##include "listes.h"
# Voir ci-dessous pour la representation des types Noeud et Liste
##include "memoire.h" //pour verification de la coherence
#
#
#/*
#Code des fonctions definies dans le module (entetes dans memoire.h):
# - init_mem, my_malloc et my_free
#
#Pour simplifier on alloue la memoire par blocs de taille fixe (la taille
#d'un noeud). Les blocs libres sont stockes dans une pile.
#*/
#
##define MAX 200 // nombre maximum de blocs
#
	.data

#static Noeud memoire[MAX] ; // On reserve MAX blocs
# Le type noeud est defini dans listes.h. Comme indiqué dans listes.s,
# Un élément de type Noeud sera represente'
# dans une zone 12 octets (4 pour le champ pred et 4 pour le champ suiv et
# 4 pour le champ info). Le champ pred est a un deplacement 0 par rapport
# au debut de cette zone, le champ suiv a un deplacement de 4, et le
# champ info a un deplacement de 8
	.align 2	
memoire:
	.space 2400 # ON NE RESPECTE PAS LA SEMANTIQUE DU C QUI DIT
		    # QUE TOUTES LES VARIABLES GLOBALES SONT INITIALISEES
                    # A ZERO 
#static Liste blocs_libres ; // Sommet de la pile des blocs libre
#Le type Liste est defini dans listes.h . Une liste est un pointeur
#sur un Noeud. Un élément de type Liste occupe 4 octets en mémoire
# ou dans un registre (cf listes.s).
blocs_libres:
	.word 0
#
#/* init_mem : Initialise les structures de donnees utilisees pour gerer
#              l'allocation et la liberation de la memoire 
#              On met tous les blocs libre sur une pile. 
#*/
#
#void init_mem(void)
	.text
	.globl init_mem
init_mem: 
#{
#   int i ; i dans $t0
#   
#   i=0 ;
    li $t0, 0;
#   do 
dowhile:
#   {
#       memoire[i].suiv = (Noeud *)(&memoire[i+1]);
        li $t1, 12
        mul $t1, $t0, $t1
        la $t1, memoire($t1) # &memoire[i] => $t1
        #&memoire[i+1] = &memoire + 12
        #&memoire[i] = &memoire + 4
        addi $t2, $t1, 12 # &memoire[i+1]
        sw $t2, 4($t1)
#       i=i+1;
        addi $t0, $t0, 1
#   } while (i<MAX-1);
    li $t1, 199
    blt $t0, $t1, dowhile
#   memoire[MAX-1].suiv = NULL ;
    li $t1, 12
    li $t0, 199 # MAX-1 => $t0
    mul $t1, $t0, $t1
    la $t1, memoire($t1) # &memoire[i] => $t1 
    sw $0, 4($t1)
#   blocs_libres = memoire ;
    la $t0, memoire($0) # memoire => $t0
    sw $t0, blocs_libres($0) # blocs_libres = memoire
#
#}
    jr $ra
#/* my_malloc : alloue un bloc de taille TAILLE_NOEUD (fixe: cf listes.h) et 
#               retourne l'adresse du bloc (retourne NULL si allocation 
#               impossible)
#*/
#void *my_malloc(void)
# resultat dans $v0
	.globl my_malloc
my_malloc:
#{  
#   Liste p; p dans $t0
#
#   p =  blocs_libres ;
    la $t0, blocs_libres($0)
#   if (p!=NULL)
    beq $t0, $0, pEstNULL
#   {
#       blocs_libres = blocs_libres->suiv ; blocs_libres dans $t0 
        lw $t1, 4($t0) # blocs_libres->suiv => $t1
        sw $t1, blocs_libres($0)
#   }
pEstNULL:
#   return((void *)p);
    addi $v0, $t0, 0
#}
	jr $ra
#
#/* my_free : libere le bloc passe en parametre.
#     ajoute le bloc au sommet de la pile des blocs
#     libres
#*/
#void my_free(void *bloc)
	.globl	my_free
my_free:
	jr $ra # A REMPLACER PAR LA TRADUCTION DU CODE C CI-DESSOUS 
#{
#   ((Liste)bloc)->suiv = blocs_libres ;
#   blocs_libres = (Liste)bloc ;
#}
#/*----------------fin memoire.s--------------------------------------*/
#
