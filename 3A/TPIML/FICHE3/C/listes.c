/*
-------------------------------------------------------------------
Nom du fichier : listes.c
Auteur : 
Objet : Module implantant les listes d'entiers doublement chainees 
        triees.
--------------------------------------------------------------------
*/
#include <stdio.h> //pour la constante NULL 

#include "listes.h" //pour verification de la coherence et définition
                    // des types Liste et Noeud
#include "memoire.h"
#include "interface.h"

/*
Code des fonctions definies dans le module (entetes dans listes.h):
 - creer_liste_vide, rechercher, inserer, afficher_liste, ...
*/

//initialisation des structures de donnees pour la gestion memoire
void init(void)
{
   init_mem();
}

// les fonction de manipulation de listes
Liste creer_liste_vide(void)
{
  return(NULL);
}


Liste inserer_tete(Liste l, int x)
/* 
insere l'entier x dans la liste l et retourne la liste 
resultat
*/
{
      Noeud * p;

      p = (Noeud *)my_malloc();
     if (p==NULL)
     {
          afficher_chaine("insertion impossible : memoire pleine\n");
          return(l);
     }   
     p->info = x ;
     if (l == NULL)
     { 
          p->pred = p ;
          p->suiv = p ;
     }
     else
     {
          p->pred = l->pred; ;
          p->suiv = l ;
          l->pred->suiv = p ;
          l->pred = p ;
     }
     return(p) ;
}

int rechercher(Liste l, int x)
/* 
retourne 1 si x est dans l, 0 sinon
*/
{

    Noeud * p = l;

    if (l == NULL) return (0);
    while ((p->info != x) && (p->suiv!=l)) 
    {
        p=p->suiv ;
    }
    if (p->info == x)
    {
       return(1) ;
    }
    else
    {
       return(0) ;
    }
}

void afficher_liste(Liste l)
/*
affiche les elements de la liste l
*/
{
     Noeud * p = l;

     if (l == NULL)
     {
        afficher_chaine("Liste vide");
     }
     else
     {      
        do
        { 
             afficher_chaine(" ");
             afficher_entier(p->info);
             p=p->suiv ;
        } while ((p!=l));
    }
    afficher_chaine("\n");
}

void afficher_liste_inverse(Liste l)
/*
affiche les elements de la liste l dans l'ordre inverse
*/
{
     Noeud * p = l;

     if (l == NULL)
     {
        afficher_chaine("Liste vide");
     }
     else
     {      
        l = l-> pred ; 
        p = l ;
        do
        {
             afficher_chaine(" ");
             afficher_entier(p->info);
             p=p->pred ;
        } while ((p!=l));
    }
    afficher_chaine("\n");
}

Liste supprimer_tete(Liste l)
/* Supprime l'element en tete de la liste l et retourne
  la liste resultat 
*/
{
   Noeud *p;

   if (l==NULL)
      return (l);
   if (l->pred == l)
      {
        my_free(l);
        return(NULL) ;
      }
   p= l->suiv ;
   p->pred = l->pred ;
   l->pred->suiv = p;
   my_free(l);
   return(p); 
}


Liste supprimer_queue(Liste l)
/* Supprime l'element en queue de la liste l et retourne
  la liste resultat 
*/
{
   Noeud *p;

   if (l==NULL)
      return (l);
   if (l->pred == l)
      {
        my_free(l);
        return(NULL) ;
      }
   p=l->pred ;
   l->pred = p->pred ;
   p->pred->suiv = l;
   my_free(p);
   return(l);
}
/*--------------------fin listes.c---------------------------*/

