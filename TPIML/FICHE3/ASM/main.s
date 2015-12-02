#/*
#-------------------------------------------------------------------
#Nom du fichier : main.s (traduction de main.c)
#Auteur :
#Objet : Module principale 
#--------------------------------------------------------------------
#*/
#
##include <stdio.h>
##include "listes.h"
# Voir listes.s pour la representation des types Liste et Noeud.
##include "interface.h"
#
#/*
#cette fonction affiche un menu qui donne les commandes disponibles
#pour effectuer les operations sur les listes  
#*/
#static void menu(void)
	.text
menu :
# menu appelle la fonction afficher_chaine.
# on sauvegarde l'adresse de retour de menu ($ra) sur la pile
	sw $ra, -4($sp)
	addiu $sp, $sp, -4
#
#	afficher_chaine("------------------Menu-----------------\n");
	la $a0, chmenu
	jal afficher_chaine
#	afficher_chaine(" 1 : Creer une liste vide \n");
	la $a0, ch1
	jal afficher_chaine
#	afficher_chaine(" 2 : Inserer un nouvel element \n");
	la $a0, ch2
	jal afficher_chaine
#	afficher_chaine(" 3 : rechercher un element \n");
	la $a0, ch3
	jal afficher_chaine
#	afficher_chaine(" 4 : Afficher la liste \n");
	la $a0, ch4
	jal afficher_chaine
#	afficher_chaine(" 5 : Afficher la liste dans l'ordre inverse\n");
	la $a0, ch5
	jal afficher_chaine
#	afficher_chaine(" 6 : Supprimer l'element en tete de liste \n");
	la $a0, ch6
	jal afficher_chaine
#	afficher_chaine(" 7 : Supprimer l'element en queue de liste \n");
	la $a0, ch7
	jal afficher_chaine
#	afficher_chaine(" 0 : Quitter \n");
	la $a0, ch0
	jal afficher_chaine
#	afficher_chaine("\n");
	la $a0, alaligne
	jal afficher_chaine
#	afficher_chaine("choix : \n");
	la $a0, choix
	jal afficher_chaine
#}
#	restauration $ra et retour a l'appelant
	addiu $sp, $sp, 4
	lw $ra, -4($sp)
        jr $ra

#
#int main(void)
	.globl main
main:
# resultat dans $v0 (convention de programmation du MIPS)
#{
#    int choix ;
# la variable locale choix sera  dans le registre $s0 (sauvegarde' 
# par l'appele')
#    int nb ;
# la variable locale nb sera dans le registre $s1 (sauvegarde' 
#  par l'appele')
#    
#
#    Liste ma_liste ;
#  la variable locale ma_liste sera dans le registre $s2 (sauvegarde'
#  par l'appele')
#
	# main appelle d'autres fonctions: on sauvegardera $ra
	# main utilise $s0, $s1, et $s2. Il faudra les sauvegarder
        
	sw $ra, -4($sp)
	sw $s0, -8($sp)
	sw $s1, -12($sp)
	sw $s2, -16($sp)
	addiu $sp, $sp, -16

#    init(); // initialisations (des structures de donnees utilisees pour la
#            // gestion de la memoire) 

	jal init

#    ma_liste = creer_liste_vide() ; 
	jal creer_liste_vide # resultat dans $v0 (decide' en examinant listes.h)
        move $s2, $v0
	 
#    menu();    
	jal menu
#    choix = lire_entier() ;
	jal lire_entier # resultat dans $v0 (decide' en examinant interface.h)
        move $s0, $v0  
#    while (choix != 0)
while: beq $s0, $0, fin_while
#    {
#        switch(choix)
# on traduit le switch en utilisant une jump table.
# valeur min de choix : 1, valeur max : 7, pas de branche default
        # si choix <= 0 aller a fin_switch
	ble $s0, $0, fin_switch
        # si choix > 7 aller a fin_switch
	li $t0, 7
	bgt $s0, $t0, fin_switch
        # aller a JT[choix]
        li $t0, 4
	mul $t0, $s0, $t0
	lw $t0, JT($t0)
	jr $t0

#        {
#            case 1 : 
case1:
#                   ma_liste = creer_liste_vide() ; 
	jal creer_liste_vide
	move $s2, $v0

	j fin_switch 
#            case 2 : 
case2:
#                   afficher_chaine("nombre a inserer ? ");
	la $a0, saisieinserer # constante stockee dans la section des donnees
	jal afficher_chaine
#                   nb = lire_entier();
	jal lire_entier
	move $s1, $v0
#                   ma_liste = inserer_tete(ma_liste, nb);
	move $a0, $s2
	move $a1, $s1
	jal inserer_tete # resultat dans $v0
	move $s2, $v0
#                   break ;
	j fin_switch 
#            case 3 : 
case3:
#                   afficher_chaine("nombre a rechercher ? ");
	la $a0, saisierechercher # constante stockee dans la section des donnees
	jal afficher_chaine
#                   nb = lire_entier();
	jal lire_entier
	move $s1, $v0
#                   if(rechercher(ma_liste, nb) !=0)
	move $a0, $s2
	move $a1, $s1,
	jal rechercher # resultat dans $v0
	beq $v0, $0, else
#                        afficher_chaine (" present!\n");
	la $a0, present
	jal afficher_chaine
	b fin_if
#                   else 
else:
#                        afficher_chaine(" absent!\n");
	la $a0, absent
	jal afficher_chaine
fin_if:
#                   break;
	j fin_switch 
#            case 4 : 
case4:
#                   afficher_liste(ma_liste);
	move $a0, $s2
	jal afficher_liste
#                   break ;
	j fin_switch 
#            case 5:
case5:
#                   afficher_liste_inverse(ma_liste);
	move $a0, $s2
	jal afficher_liste_inverse
#                   break ;
	j fin_switch 
#            case 6: ma_liste = supprimer_tete(ma_liste); 
case6:
	move $a0, $s2
	jal supprimer_tete
	move $s2, $v0
#                   break ;
	j fin_switch 
#            case 7: ma_liste = supprimer_queue(ma_liste);
case7:
	move $a0, $s2
	jal supprimer_queue
	move $s2, $v0
#                   break ;
	j fin_switch # inutile car on y est deja 
#         }
fin_switch:
#         menu();
	jal menu
#         choix = lire_entier() ;
	jal lire_entier 
        move $s0, $v0  
#    }
	j while
fin_while:
#    
#
#
#return(0);
	li $v0, 0
	# restauration $si et $ra puis retour a l'appelant
	addiu $sp, $sp, 16
	lw $ra, -4($sp)
	lw $s0, -8($sp)
	lw $s1, -12($sp)
	lw $s2, -16($sp)
	jr $ra

#}

	.data
# constantes chaines de caracteres utilisees dans la fonction menu
chmenu:	.asciiz "------------------Menu-----------------\n"
ch1:	.asciiz " 1 : Creer une liste vide \n"
ch2: 	.asciiz " 2 : Inserer un nouvel element \n"
ch3:	.asciiz " 3 : rechercher un element \n"
ch4:	.asciiz " 4 : Afficher la liste \n"
ch5:	.asciiz " 5 : Afficher la liste dans l'ordre inverse\n"
ch6:	.asciiz " 6 : Supprimer l'element en tete de liste \n"
ch7:	.asciiz " 7 : Supprimer l'element en queue de liste \n"
ch0:	.asciiz " 0 : Quitter \n"
alaligne: .asciiz "\n"
choix :	.asciiz "choix : \n"

#constantes chaines de caracteres utilisees dans main
saisieinserer: .asciiz  "nombre a inserer ? "
saisierechercher: .asciiz "nombre a rechercher ? "
present: .asciiz " present!\n"
absent: .asciiz " absent!\n"

# jump table
	.align 2
JT : 	.word 0 # mot perdu car choix=0 n'est pas une branche du switch	
	.word case1
	.word case2
	.word case3
	.word case4
	.word case5
	.word case6
	.word case7
	

#/*------------------------fin main.s------------------------------*/
