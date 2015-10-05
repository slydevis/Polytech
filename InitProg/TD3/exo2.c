/* 
 * @file exo2.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 29/09/2015
 * @version 1
 * Polytech Marseille
 * Exercice 2 du TD3
 * Ce programme doit afficher rechercher le plus petit élément d'un 
 * tableau de taille N
 */
 
#include<stdio.h>

#define N 10

int main() {
    int i;
    int T[N] = {5, 4, 8, 9, 3, 1, 8, 9, 44, 42};
    
    int imin = 0;
    int min = T[0];
    
    for(i = 1; i < N; ++i) {
        if(T[i] < min) {
            imin = i;
            min = T[i];
        }
    } 

    // Doit afficher trouver l'indice 5 avec pour valeur 1
    printf("Le plus petit élément est sur T[%d] = %d\n", imin, min);
        
    return 0;
}
 
