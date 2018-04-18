#/*
#-------------------------------------------------------------------
#Nom du fichier : interface.s (traduction de interface.c) 
# Auteur :
#Objet : Module implantant les fonctions de saisie et d'affichage
#        On utilise un module a part pour la traduction en langage
#        d'assemblage  
#--------------------------------------------------------------------
#*/
##include <stdio.h> // pour les fonctions printf et scanf
##include "interface.h" //pour verification de la coherence
#le fichier interface.h doit être inclus ici. (aucune directive
# dans ce fichier ne conduit à une instruction ou directive en 
# langage d'assemblage)

#
#/* lire_entier : Lit un entier a la console et retourne sa valeur 
#*/
#int lire_entier(void)
#debut de la section de code
	.text
	.globl lire_entier
lire_entier:
# le resultat sera retourne dans $v0 (convention de programmation du MIPS)
# on utilisera le service systeme read_int du MIPS  (service 5)
#{  int x;
# x sera alloue dans $v0
#   scanf("%d",&x);
#   on utilise pas la fonction scanf. A la place on utilise
#   le service systeme read_int du MIPS
    li $v0, 5
    syscall   # l'entier lue est dans $v0
#   return(x);
# le resultat est dans $v0, il ne reste plus
#  qu'a retourner a l'appelant.
    jr $ra    
#}
#
#/* afficher_entier : affiche a la console l'entier passe en parametre 
#*/
#void afficher_entier(int x)
	.globl afficher_entier
afficher_entier:
# Le parametre x sera passe dans le registre $a0 (convention de 
# programmation du MIPS).
# On utilisera le service systeme print_int qui permet d'afficher
# un entier a la console (service 1, l'entier doit etre dans $a0)
#{
#  printf("%d", x);
	li $v0, 1
        # l'entier a afficher est deja dans $a0
        syscall 
#}
	#retour a l'appelant
        jr $ra

#
#/* afficher_chaine : affiche a la console la chaine passee en parametre 
#*/
#void afficher_chaine(char *s)
	.globl afficher_chaine
afficher_chaine :
# Le parametre s sera passe dans $a0 (convention de programmation du MIPS)
# On utilisera le service systeme print_string pour afficher une chaine
# de caracteres (service 4, l'adresse de la chaine a afficher doit etre
# dans $a0)
#{
#  printf("%s", s);
	li $v0, 4
        # $a0 contient deja s (adresse de la chaine a afficher)
        syscall
#}
	#retour a l'appelant
        jr $ra
#
#/*-----------------fin interface.s-----------------------------------*/
#
