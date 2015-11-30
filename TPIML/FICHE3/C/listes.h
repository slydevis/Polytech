/*
-------------------------------------------------------------------
Nom du fichier : listes.h
Auteur :
Objet : entete du module implantant les listes d'entiers doublement chainees
        triees  
--------------------------------------------------------------------
*/

#ifndef _LISTES_H_ 
#define _LISTES_H_

/*
Definitions des types
Representation des listes circulaires doublement chainees
 avec 2 liens de chainage
*/
typedef struct maillon{
        struct maillon *pred ;
        struct maillon *suiv ;
        int info;
}Noeud, *Liste ;

#define TAILLE_NOEUD (sizeof(Noeud)) //Utilise' seulement dans les commentaires


//initialisation des structures de donnees pour la gestion de la memoire
void init();



/*
declaration des fonctions definies dans le module (entetes)
 - creer_liste_vide, rechercher, inserer, afficher_liste,
   afficher_liste_inverse...
*/

/* creer_liste_vide : retourne la liste vide
*/
Liste creer_liste_vide(void);

/* inserer_tete :
insere l'entier x dans la liste l et retourne la liste
resultat
*/
Liste inserer_tete(Liste l, int x);

/* rechercher : retourne 1 si x est dans l, 0 sinon
*/
int rechercher(Liste l, int x);

/* afficher_liste : affiche les elements de la liste l
*/
void afficher_liste(Liste l);

/* afficher_liste_inverse :
affiche les elements de la liste l dans l'ordre inverse
*/
void afficher_liste_inverse(Liste l);

/* supprimere_tete :
 Supprime l'element en tete de la liste l et retourne
  la liste resultat
*/
Liste supprimer_tete(Liste l);

/* supprimer_queue :
  Supprime l'element en queue de la liste l et retourne
  la liste resultat
*/
Liste supprimer_queue(Liste l);


/*---------------------- fin listes.h ---------------------------*/

#endif

