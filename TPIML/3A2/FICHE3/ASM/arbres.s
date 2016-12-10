#/*
#-------------------------------------------------------------------
#Nom du fichier : arbres.s
#Auteur :
#Objet : Module implantant les arbres binaires de recherche
#        contenant des entiers. Les noeuds sont doublement chainees.
#--------------------------------------------------------------------
#*/
##include <stdio.h> //pour la constante NULL
#
##include "arbres.h" //pour verification de la coherence et définition
#                    // des types Arbre et Noeud
# arbres.h définit les types Noeud et Arbre.
# Un élément de type Noeud sera represente'
# dans une zone 16 octets (4 pour le champ info,
# 4 pour le champ fils_gauche,  4 pour le champ fils_droit,
# et 4 pour le champ pere).
#  Le champ info est a un deplacement 0 par rapport
# au debut de cette zone, le champ fils_gauche a un deplacement de 4,
# le champ fils_droit a un deplacement de 8,
# et le champ pere a un deplacement de 12.
# Un Arbre est un pointeur sur un Noeud. Un élément de type Arbre
# occupe 4 octets en mémoire ou dans un registre.

##include "memoire.h"
# memoire.h ne contient que des prototypes de fonctions.
##include "interface.h"
# interface.h ne contient que des prototypes de fonctions.
#
#/*
# Code des fonctions definies dans le module (entetes)
# - creer_arbre_vide, inserer, afficher_arbre_croissant,rechercher,
# afficher_min, supprime_min, ...
# */
#
#Arbre creer_arbre_vide(void)
        .text
	.globl creer_arbre_vide
creer_arbre_vide:
#/* creer_arbre_vide : retourne l'arbre vide
#*/
#{
#  return(NULL);
	move $v0, $0
	# retour a l'appelant
	jr $ra
#}
#
#
#Arbre inserer(Arbre a, int x)
	.globl inserer
# parametres : a dans $a0, x dans $a1
# resultat dans $v0
#/* inserer :
#insere l'entier x dans l'arbre binaire de recherche a et retourne
#l'arbre resultat
#*/
inserer:
#{
#      Noeud * p;
#      p dans $s0
#      Noeud * q;
#      q dans $s1
#      Noeud * r;
#      r dans $s2

#     Sauvegarde des registres $ra, $s0, $s1, $s2
  sw $ra, -4($sp)
  sw $s0, -8($sp)
  sw $s1, -12($sp)
  sw $s2, -16($sp)
  addiu $sp, $sp, -16
#      p = (Noeud *)my_malloc();
  jal my_malloc
  move $s0, $v0
#     if (p==NULL)
  bnez $s0, p_not_null_inserer
#     {
# sauvegarde de $a0, $a1
  sw $a0, -4($sp)
  sw $a1, -8($sp)
  addiu $sp, $sp, -8
#          afficher_chaine("insertion impossible : memoire pleine\n");
  la $a0, memoire_pleine
  jal afficher_chaine
# restauration de $a0 et $a1
  addiu $sp, $sp, 8
  lw $a0, -4($sp)
  lw $a1, -8($sp)
#          return(a);
  move $v0, $a0
  j fin_inserer
#     }
p_not_null_inserer:
#     p->info = x ;
  sw $a1, 0($s0)
#     p->fils_gauche = NULL ;
  sw $0, 4($s0)
#     p->fils_droit = NULL ;
  sw $0, 8($s0)
#     if (a == NULL)
  bnez $a0, a_not_null_inserer
#     {
#          p->pere = NULL ;
  sw $0, 12($s0)
#          return(p);
  move $v0, $s0
  j fin_inserer
#     }
a_not_null_inserer:
#     q=a;
  move $s1, $a0
do_while_inserer:
#     do
#     {
#          r=q;
  move $s2, $s1
#          if (x < q->info)
  lw $t0, 0($s1)
  bge $a1, $t0, x_higher_q_info
#          {
#              q=q->fils_gauche ;
  lw $t0, 4($s1)
  move $s1, $t0
  j fin_x_higher_q_info
#          }
x_higher_q_info:
#          else
#          {
#              q=q->fils_droit ;
  lw $t0, 8($s1)
  move $s1, $t0
#          }
fin_x_higher_q_info:
#     }while(q!=NULL);
  bnez $s1, do_while_inserer
#     p->pere = r ;
  sw $s2, 12($s0)
#     if (x < r->info)
  lw $t0, 0($s2)
  bge $a1, $t0, x_higher_r_info
#     {
#         r->fils_gauche=p ;
  sw $s0, 4($s2)
#     }
  j fin_x_higher_r_info
#     else
#     {
x_higher_r_info:
#         r->fils_droit=p ;
  sw $s0, 8($s2)
#     }
fin_x_higher_r_info:
#     return(a);
  move $v0, $a0
fin_inserer:
# restauration de $ra, $s0, $s1, $s2
  addiu $sp, $sp, 16
  lw $ra, -4($sp)
  lw $s0, -8($sp)
  lw $s1, -12($sp)
  lw $s2, -16($sp)
  jr $ra
#}
#
#void afficher_arbre_croissant(Arbre a)
# parametre a dans $a0
#/*
#/* afficher_arbre_croissant : affiche les elements de l'arbre a dans
#   l'ordre #croissant
#*/
	.globl afficher_arbre_croissant
afficher_arbre_croissant:
#{
# sauvegarde de $ra et de $a0
  sw $ra, -4($sp)
  sw $a0, -8($sp)
  addiu $sp, $sp, -8
#     if (a!= NULL)
#     {
  beqz $a0, a_null_afficher_arbre_croissant
#        afficher_arbre_croissant(a->fils_gauche);
  lw $a0, 4($a0)
  jal afficher_arbre_croissant
#        afficher_chaine(" ");
  la $a0, space
  jal afficher_chaine
#        afficher_entier(a->info);
  lw $a0, 0($sp)
  lw $a0, 0($a0)
  jal afficher_entier
#        afficher_arbre_croissant(a->fils_droit);
  lw $a0, 0($sp)
  lw $a0, 8($a0)
  jal afficher_arbre_croissant
#     }
a_null_afficher_arbre_croissant:
# restauration de $ra et de $a0
  addiu $sp, $sp, 8
  lw $ra, -4($sp)
  lw $a0, -8($sp)
  jr $ra
#}
#
#int rechercher(Arbre a, int x)
# parametres : a dans $a0, x dans $a1
# resultat dans $v0
#/* rechercher : retourne 1 si x est dans l'arbre a, 0 sinon
#*/
	.globl rechercher
rechercher:
# sauvegarde de $ra
  sw $ra, -4($sp)
  addiu $sp, $sp, -4
#{
#     if (a == NULL) return(0) ;
  bnez $a0, a_not_null_rechercher
  li $v0, 0
  j fin_rechercher
a_not_null_rechercher:
  lw $t0, 0($a0) # a->info
#     if (a->info == x) return(1) ;
  bne $t0, $a1, a_info_not_equal_x
  li $v0, 1
  j fin_rechercher
a_info_not_equal_x:
  ble $t0, $a1, else_rechercher
#     if (a->info > x)
#     {
# sauvegarde de $a0 et $a1
  sw $a0, -4($sp)
  sw $a1, -8($sp)
  addiu $sp, $sp, -8
#         return(rechercher(a->fils_gauche, x));
  lw $a0, 4($a0) # a->fils_gauche
# x déjà dans $a1
  jal rechercher
# restauration de $a0 et $a1
  addiu $sp, $sp, 8
  lw $a0, -4($sp)
  lw $a1, -8($sp)
# resultat déjà dans $v0
  j fin_rechercher
#     }
else_rechercher:
#     else
#     {
# sauvegarde de $a0 et $a1
  sw $a0, -4($sp)
  sw $a1, -8($sp)
  addiu $sp, $sp, -8
#         return(rechercher(a->fils_droit, x));
  lw $a0, 8($a0) # a->fils_droit
# x déjà dans $a1
  jal rechercher
#restauration de $a0 et $a1
  addiu $sp, $sp, 8
  lw $a0, -4($sp)
  lw $a1, -8($sp)
# resultat déjà dans $v0
  j fin_rechercher
#     }
fin_rechercher:
# restauration de $ra
  addiu $sp, $sp, 4
  lw $ra, -4($sp)
  jr $ra
#}
#
#void afficher_min(Arbre a)
# parametre a dans $a0
#/*
#/* afficher_min :
#  Affiche la valeur minimale dans l'arbre a
#*/
	.globl afficher_min
afficher_min:
# sauvegarde de $ra et $s0
  sw $ra, -4($sp)
  sw $s0, -8($sp)
  sw $a0, -12($sp)
  addiu $sp, $sp, -12
#{
#      Noeud *p = a;
# p sera dans $s0
  move $s0, $a0
#
#      if (a==NULL)
#      {
  bnez $a0, a_not_null_afficher_min
#          printf("\nArbre vide!\n");
  la $a0, arbre_vide
  jal afficher_chaine
  j fin_afficher_min
#      }
a_not_null_afficher_min:
#      else
#      {
while_affiche_min:
# calcul de p->fils_gauche dans $t0
  lw $t0, 4($s0)
  beqz $t0, fin_while_affiche_min
#          while(p->fils_gauche != NULL)
#          {
#               p=p->fils_gauche ;
  move $s0, $t0 # p->fils_gauche
#          }
  bnez $t0, while_affiche_min
fin_while_affiche_min:
#          afficher_chaine("\n");
  la $a0, newLine
  jal afficher_chaine
#          afficher_entier(p->info);
  lw $a0, 0($s0) # p->info
  jal afficher_entier
#          afficher_chaine("\n");
  la $a0, newLine
  jal afficher_chaine
#      }
fin_afficher_min:
# restauration de $ra
  addiu $sp, $sp, 12
  lw $ra, -4($sp)
  lw $s0, -8($sp)
  lw $a0, -12($sp)
  jr $ra
#}
#
#Arbre supprimer_min(Arbre a)
# parametre a dans $a0
# resultat dans $v0
#/*
#/* supprimer_min :
#  Supprime de l'arbre a un element ayant une valeur minimale et retourne
#  l'arbre resultat
#*/
	.globl supprimer_min
supprimer_min:
#{
# sauvegarde de $ra et de $s0
  sw $ra, -4($sp)
  sw $s0, -8($sp)
  addiu $sp, $sp, -8
#      Noeud *p = a;
# p dans $s0
  move $s0, $a0
#      if (a==NULL)
#      {
  bnez $a0, a_not_null_supprimer_min
#          printf("\nArbre vide!\n");
  la $a0, arbre_vide
  jal afficher_chaine
#          return(NULL);
  li $v0, 0
  j fin_supprimer_min
#      }
a_not_null_supprimer_min:
while_supprimer_min:
#      while(p->fils_gauche != NULL)
#      {
# p->fils_gauche dans $t0
  lw $t0, 4($s0)
  beqz $t0, fin_while_supprimer_min
#           p=p->fils_gauche ;
  move $s0, $t0
  j while_supprimer_min
#      }
fin_while_supprimer_min:
#      if (p->fils_droit != NULL)
#      {
  lw $t0, 8($s0) # p->fils_droit
  beqz $t0, p_fils_droit_null_supprimer_min
#          p->fils_droit->pere=p->pere ;
  lw $t1, 12($s0) # p->pere
  sw $t1, 12($t0) # p->fils_droit->pere
#         if (p != a)
  beq $s0, $a0, p_egal_a_supprimer_min
#         {
#              p->pere->fils_gauche = p->fils_droit ;
  lw $t0, 8($s0) # p->fils_droit
  lw $t1, 12($s0) # p->pere
  sw $t0, 4($t1) # p->pere->fils_gauche
  j fin_supprimer_min
#         }
p_egal_a_supprimer_min:
#         else
#         {
#              a = a->fils_droit ;
  lw $t0, 8($a0) # a->fils_droit
  move $a0, $t0
  j fin_supprimer_min
#         }
#      }
p_fils_droit_null_supprimer_min:
#      else // p n'a pas de fils droit
#      {
#             if (p == a) a=NULL ;
  bne $s0, $a0, p_pas_egal_a_supprimer_min
  move $a0, $0
#  j fin_supprimer_min
p_pas_egal_a_supprimer_min:
#             else p->pere->fils_gauche=NULL ;
  lw $t0, 12($s0) # p->pere
  sw $0, 4($t0) # p->pere->fils_gauche
#      }
fin_supprimer_min:
# sauvegarde de $a0
  sw $a0, -4($sp)
  addiu $sp, $sp, -4
#      my_free(p);
  move $a0, $s0
  jal my_free
# restauration de $a0
  addiu $sp, $sp, 4
  lw $a0, -4($sp)
#      return(a);
  move $v0, $a0
# restauration de $ra et $s0
  addiu $sp, $sp, 8
  lw $ra, -4($sp)
  lw $s0, -8($sp)
  jr $ra
#}
#
#/*--------------------fin arbres.s---------------------------*/
#

  .data
memoire_pleine: .asciiz "insertion impossible : memoire pleine\n"
space: .asciiz " "
arbre_vide: .asciiz "\nArbre vide!\n"
newLine: .asciiz "\n"
