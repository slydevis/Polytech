/*
-------------------------------------------------------------------
Nom du fichier : main.c
Auteur :
Objet : Module principale 
--------------------------------------------------------------------
*/

#include <stdio.h>
#include "listes.h"
#include "interface.h"

/*
cette fonction affiche un menu qui donne les commandes disponibles
pour effectuer les operations sur les listes  
*/
static void menu(void)
{
	afficher_chaine("------------------Menu-----------------\n");
	afficher_chaine(" 1 : Creer une liste vide \n");
	afficher_chaine(" 2 : Inserer un nouvel element \n");
	afficher_chaine(" 3 : rechercher un element \n");
	afficher_chaine(" 4 : Afficher la liste \n");
	afficher_chaine(" 5 : Afficher la liste dans l'ordre inverse\n");
	afficher_chaine(" 6 : Supprimer l'element en tete de liste \n");
	afficher_chaine(" 7 : Supprimer l'element en queue de liste \n");
	afficher_chaine(" 0 : Quitter \n");
	afficher_chaine("\n");
	afficher_chaine("choix : \n");
}

int main(void)
{
    int choix ;
    int nb ;
    

    Liste ma_liste ;

    init(); // initialisations (des structures de donnees utilisees pour la
            // gestion de la memoire) 
    ma_liste = creer_liste_vide() ; 
    menu();    
    choix = lire_entier() ;
    while (choix != 0)
    {
        switch(choix)
        {
            case 1 : 
                   ma_liste = creer_liste_vide() ; 
                   break;
            case 2 : 
                   afficher_chaine("nombre a inserer ? ");
                   nb = lire_entier();
                   ma_liste = inserer_tete(ma_liste, nb);
                   break ;
            case 3 : 
                   afficher_chaine("nombre a rechercher ? ");
                   nb = lire_entier();
                   if(rechercher(ma_liste, nb) !=0)
                        afficher_chaine (" present!\n");
                   else 
                        afficher_chaine(" absent!\n");
                   break;
            case 4 : 
                   afficher_liste(ma_liste);
                   break ;
            case 5:
                   afficher_liste_inverse(ma_liste);
                   break ;
            case 6: ma_liste = supprimer_tete(ma_liste); 
                   break ;
            case 7: ma_liste = supprimer_queue(ma_liste);
                   break ;
         }
         menu();
         choix = lire_entier() ;
    }

    


return(0);
}
/*------------------------fin main.c------------------------------*/
