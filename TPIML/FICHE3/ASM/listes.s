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
	move $v0, $0 # la constante NULL est deinie comme
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
#      Noeud * p; p dans $t0
#
# Sauvegarde de l'ardresse de retour et de $a0
    sw $a0, -4($sp)
    sw $ra, -8($sp)
    addi $sp, $sp, -8
#      p = (Noeud *)my_malloc();
    jal my_malloc
    move $t0, $v0
#     if (p==NULL)
    bne $t0, $0, fin_p_NULL
#     {
#          afficher_chaine("insertion impossible : memoire pleine\n");
        la $a0, fullmemory
        jal afficher_chaine
        # Resteauration de l
        lw $a0, 4($sp)
        addi $sp, $sp, -4
#          return(l);
        move $v0, $a0
        # Resteauration de l'adresse de retour
        addiu $sp, $sp, 4
        lw $ra, -4($sp)
        jr $ra
#     }
fin_p_NULL:   
#     p->info = x ;
#     if (l == NULL)
#     { 
#          p->pred = p ;
#          p->suiv = p ;
#     }
#     else
#     {
#          p->pred = l->pred; ;
#          p->suiv = l ;
#          l->pred->suiv = p ;
#          l->pred = p ;
#     }
#     return(p) ;
#}
	jr $ra
#
#int rechercher(Liste l, int x)
# parametres : l dans $a0, x dans $a1
# resultat dans $v0
#/* 
#retourne 1 si x est dans l, 0 sinon
#*/
	.globl rechercher

rechercher:
	jr $ra ### A REMPLACER PAR LA TRADUCTION DU CODE C  CI-DESSOUS
#{
#
#    Noeud * p = l;
#
#    if (l == NULL) return (0);
#    while ((p->info != x) && (p->suiv!=l)) 
#    {
#        p=p->suiv ;
#    }
#    if (p->info == x)
#    {
#       return(1) ;
#    }
#    else
#    {
#       return(0) ;
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
	jr $ra ### A REMPLACER PAR LA TRADUCTION DU CODE C  CI-DESSOUS
#{
#     Noeud * p = l;
#
#     if (l == NULL)
#     {
#        afficher_chaine("Liste vide");
#     }
#     else
#     {      
#        do
#        { 
#             afficher_chaine(" ");
#             afficher_entier(p->info);
#             p=p->suiv ;
#        } while ((p!=l));
#    }
#    afficher_chaine("\n");
#}
#
#void afficher_liste_inverse(Liste l)
#/*
#affiche les elements de la liste l dans l'ordre inverse
#*/
# parametre l dans $a0
	.globl afficher_liste_inverse
afficher_liste_inverse:
	jr $ra ### A REMPLACER PAR LA TRADUCTION DU CODE C  CI-DESSOUS
#{
#     Noeud * p = l;
#
#     if (l == NULL)
#     {
#        afficher_chaine("Liste vide");
#     }
#     else
#     {      
#        l = l-> pred ; 
#        p = l ;
#        do
#        {
#             afficher_chaine(" ");
#             afficher_entier(p->info);
#             p=p->pred ;
#        } while ((p!=l));
#    }
#    afficher_chaine("\n");
#}
#
#Liste supprimer_tete(Liste l)
#/* Supprime l'element en tete de la liste l et retourne
#  la liste resultat 
#*/
# parametre l dans $a0, resultat dans $v0
	.globl supprimer_tete
supprimer_tete:
	jr $ra ### A REMPLACER PAR LA TRADUCTION DU CODE C  CI-DESSOUS
#{
#   Noeud *p;
#
#   if (l==NULL)
#      return (l);
#   if (l->pred == l)
#      {
#        my_free(l);
#        return(NULL) ;
#      }
#   p= l->suiv ;
#   p->pred = l->pred ;
#   l->pred->suiv = p;
#   my_free(l);
#   return(p); 
#}
#
#
#Liste supprimer_queue(Liste l)
# parametre l dans $a0, resultat dans $v0
	.globl supprimer_queue
supprimer_queue:
	jr $ra ### A REMPLACER PAR LA TRADUCTION DU CODE C  CI-DESSOUS
#/* Supprime l'element en queue de la liste l et retourne
#  la liste resultat 
#*/
#{
#   Noeud *p;
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
