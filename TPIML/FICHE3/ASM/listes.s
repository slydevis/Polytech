#/*
#-------------------------------------------------------------------
#Nom du fichier : listes.s (traduction de listes.s)
#Auteur : 
#Objet : Module implantant les listes d'entiers doublement chainees 
#        triees.
#--------------------------------------------------------------------
#*/
##include <stdio.h> //pour la constante NULL

##include "listes.h" //pour verification de la coherence et définition des types
#                    //Noeud et Liste.
# listes.h définit les types Noeud et Liste. Un Noeud sera represente'
# dans une zone mémoire de 12 octets (4 pour le champ pred et 4 pour
# le champ suiv et 4 pour le champ info). Le champ pred est a un
# deplacement 0 par rapport au debut de cette zone, le champ suiv a un
# deplacement de 4, et le champ info a un deplacement de 8
# Une liste est un pointeur sur un Noeud. Un élément de type Liste
# occupe 4 octets en mémoire ou dans un registre.

##include "memoire.h"
# memoire.h ne contient que des prototypes de fonctions.
##include "interface.h"
# interface.h ne contient que des prototypes de fonctions.
#
#/*
#Code des fonctions definies dans le module (entetes dans listes.h):
# - creer_liste_vide, rechercher, inserer, afficher_liste, ...
#*/
#
#//initialisation des structures de donnees pour la gestion memoire
	.text

#void init(void)
	.globl init
init: 
        #Sauvegarde adresse de retour
	sw $ra, -4($sp)
	addiu	$sp, $sp, -4
#{	
#   init_mem();
	jal init_mem
#}
	#restauration adresse de retour
	addiu	$sp, $sp, 4
	lw $ra, -4($sp)
	# retour a l'appelant
	jr $ra

#
#// les fonction de manipulation de listes
#Liste creer_liste_vide(void)
	.globl creer_liste_vide
creer_liste_vide:
# resultat dans $v0
#{
#  return(NULL);
	move $v0, $0 # la constante NULL est definie comme
                    # etant egale a 0 dans stdio.h
        # retour a l'appelant
	jr  $ra
#}
#
#
#Liste inserer_tete(Liste l, int x)
	.globl inserer_tete
# parametres : l dans $a0, x dans $a1
# resultat dans $v0
#/* 
#insere l'entier x dans la liste l et retourne la liste 
#resultat
#*/

inserer_tete:
#{
#   Noeud * p; p dans $t0
#
#   Sauvegarde de l'ardresse de retour et de $a0
    sw $a0, -4($sp)
    sw $ra, -8($sp)
    addi $sp, $sp, -8
#   p = (Noeud *)my_malloc();
    jal my_malloc
    move $t0, $v0
#   if (p==NULL)
    bne $t0, $0, fin_p_NULL
#   {
#       afficher_chaine("insertion impossible : memoire pleine\n");
        la $a0, fullmemory
        jal afficher_chaine
        # Restauration de l
        addi $sp, $sp, 8
        lw $a0, -4($sp)
        move $v0, $a0
        # Restauration de l'adresse de retour
        lw $ra, -8($sp)
        # return(l);
        jr $ra
#   }
fin_p_NULL:   
#   p->info = x ;
    sw $a1, 8($t0);
    bne $a0, $0, lNotNull 
#   if (l == NULL)
#   { 
#       p->pred = p ;
        sw $t0, 0($t0)
#       p->suiv = p ;
        sw $t0, 4($t0) 
        beq $0, $0, finIf
#  }
lNotNull:
#  else
#  {        
#       p->pred = l->pred;
        lw $t1, 0($a0) # l->pred dans $t1
        sw $t1, 0($t0)
#       p->suiv = l ;
        sw $a0, 4($t0)
#       l->pred->suiv = p ;
        lw $t1, 0($a0) # l->pred dans $t1 (inutile)
        sw $t0, 4($t1) # l->pred->suiv = p
#       l->pred = p ;
        sw $t0, 0($a0)
#  }
finIf:
    # Restauration de l'adresse de retour
    addiu $sp, $sp, 8
    lw $ra, -8($sp)
    move $v0, $t0
#  return(p) ;
	jr $ra
#}
#
#int rechercher(Liste l, int x)
# parametres : l dans $a0, x dans $a1
# resultat dans $v0
#/* 
#retourne 1 si x est dans l, 0 sinon
#*/
	.globl rechercher

rechercher:
#{
#
#    Noeud * p = l; p dans $t0
#
#    if (l == NULL) return (0);
    bne $a0, $0, lNotNullRecherche
    li $v0, 0
    jr $ra
lNotNullRecherche:
#    while ((p->info != x) && (p->suiv!=l)) 
while:
    lw $t1, 8($t0) # p->info dans $t1
    lw $t2, 4($t0) # p->suiv dans $t2
    beq $t1, $a1, finWhile
    beq $t2, $a0, finWhile
#    {
#        p=p->suiv ;
        lw $t0, 4($t0)
        beq $0, $0, while
#    }
finWhile:
#    if (p->info == x)
    bne $t1, $a1, pasTrouve
#    {
#       return(1) ;
    li $v0, 1
    jr $ra
#    }
pasTrouve:
#    else
#    {
#       return(0) ;
    li $v0, 0
    jr $ra
#    }
#}
#
#void afficher_liste(Liste l)
#/*
#affiche les elements de la liste l
#*/
# parametre l dans $a0
	.globl afficher_liste
afficher_liste:
#{
#   Sauvegarde de l'ardresse de retour et de l dans $sp
    sw $a0, -4($sp)
    sw $ra, -8($sp)
    addi $sp, $sp, -8

#     Noeud * p = l; # p dans $t0
    move $t0, $a0
#     if (l == NULL)
    bne $a0, $0, lNotNull2
#     {
#        afficher_chaine("Liste vide");
        la $a0, listeVide
        jal afficher_chaine 
        beq $0, $0, finIf2
#     }
lNotNull2:
#     else
#     {
doWhile:
#        do
#        {
#             afficher_chaine(" ");
            la $a0, spaceCar
            jal afficher_chaine
#             afficher_entier(p->info);
            lw $a0, 8($t0)
            jal afficher_entier 
#             p=p->suiv ;
            lw $t0, 4($t0)
            # Restauration de l
            lw $a0, 4($sp)
#        } while ((p!=l));
        bne $t0, $a0, doWhile
#    }
finIf2:
#    afficher_chaine("\n");
    la $a0, alaligne
    jal afficher_chaine
    
    # Restauration de l'adresse de retour
    addiu $sp, $sp, 8
    lw $ra, -8($sp)
	jr $ra
#}
#
#void afficher_liste_inverse(Liste l)
#/*
#affiche les elements de la liste l dans l'ordre inverse
#*/
# parametre l dans $a0
	.globl afficher_liste_inverse
afficher_liste_inverse:
#{
# sauvegarde de l'adresse de retour et du parametre
    sw $a0, -4($sp)
    sw $ra, -8($sp)
    addi $sp, $sp, -8
#     Noeud * p = l; p dans $t0
    move $t0, $a0
    bne $a0, $0, lNotNull3
#     if (l == NULL)
#     {
        la $a0, listeVide
        jal afficher_chaine
#        afficher_chaine("Liste vide");
        beq $0, $0, finIf3
#     }
lNotNull3:
#     else
#     {
#        l = l-> pred ;
        lw $a0, 0($a0)
#        p = l ;
        addi $t0, $a0, 0
#        do
doWhile2:
#        {
#           Sauvegarde de $a0 (la variable l)
            sw $a0, -4($sp)
            addi $sp, $sp, -4      
#             afficher_chaine(" ");
            la $a0, spaceCar
            jal afficher_chaine           
#             afficher_entier(p->info);
            lw $a0, 8($t0)
            jal afficher_entier
#             p=p->pred ;
            lw $t0, 0($t0)
             # Restauration de l
            addiu $sp, $sp, 4
            lw $a0, -4($sp)
#        } while ((p!=l));
    bne $t0, $a0, doWhile2
#    }
finIf3:
#    afficher_chaine("\n");
    la $a0, alaligne
    jal afficher_chaine
#}
    # Restauration de l'adresse de retour
    addiu $sp, $sp, 8
    lw $ra, -8($sp)
    jr $ra
#
#Liste supprimer_tete(Liste l)
#/* Supprime l'element en tete de la liste l et retourne
#  la liste resultat 
#*/
# parametre l dans $a0, resultat dans $v0
	.globl supprimer_tete
supprimer_tete:
#{
#   Sauvegarde de l'ardresse de retour
    sw $a0, -4($sp)
    sw $ra, -8($sp)
    addi $sp, $sp, -8

#   Noeud *p; p dans $t0
#   
#   if (l==NULL)
    bne $a0, $0, noRetourL
#      return (l);
    move $v0, $a0
    jr $ra
noRetourL:
    lw $t1, 0($a0) # l->prec dans $t1
#   if (l->pred == l)
    bne $t1, $a0, lPredNotL
#      {
#        my_free(l);
    jal my_free
    # Restauration de l'adresse de retour
    addiu $sp, $sp, 8
    lw $ra, -8($sp)
    move $v0, $0
	jr $ra
#        return(NULL) ;
#      }
lPredNotL:
#   p= l->suiv ;
    lw $t0, 4($a0)
    lw $t1, 0($t0) # p->pred dans $t1
#   p->pred = l->pred ;
    lw $t1, 0($a0)
#   l->pred->suiv = p;
    lw $t1, 4($t1) # p->pred->suiv dans $t1
    addi $t1, $t0, 0
#   my_free(l);
    move $t0, $a0
    jal my_free
    # Restauration de l'adresse de retour
    addiu $sp, $sp, 8
    lw $ra, -8($sp)
#   return(p); 
    move $t0, $v0
    jr $ra
#}

#Liste supprimer_queue(Liste l)
# parametre l dans $a0, resultat dans $v0
	.globl supprimer_queue
supprimer_queue:
	jr $ra ### A REMPLACER PAR LA TRADUCTION DU CODE C  CI-DESSOUS
#/* Supprime l'element en queue de la liste l et retourne
#  la liste resultat 
#*/
#{
#   Noeud *p; p dans $t0
#
#   if (l==NULL)
#      return (l);
#   if (l->pred == l)
#      {
#        my_free(l);
#        return(NULL) ;
#      }
#   p=l->pred ;
#   l->pred = p->pred ;
#   p->pred->suiv = l;
#   my_free(p);
#   return(l);
#}
.data
fullmemory: 
    .asciiz "insertion impossible : memoire pleine\n"
#/*--------------------fin listes.s---------------------------*/
#
