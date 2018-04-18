/* 
 * @file exo4.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 29/09/2015
 * @version 1
 * Polytech Marseille
 * Exercice 4 du TD3
 * Ce programme à pour objectif pour de tasser un tableau de taille N
 * contenant des éléments nul (la valeur est égale à 0)
 */
 
#include<stdio.h>
#include <stdlib.h>

#define N 10

int main() {
    int T[N] = {1, 0, 0, 0, 3, 0, 0, 0, 0, 2};
    int i, nbNoVide = 0;
    int *resultat = (int*) malloc(sizeof(int)*N);
    
    // On compte le nombre de case vide
    for(i = 0; i < N; ++i) {
        if(T[i] != 0) {
            resultat[nbNoVide] = T[i];
            nbNoVide++;
        }
    }
    
    // Affichage du résultat
    if(nbNoVide != 0) {
        printf("T[] = {");
        
        for(i = 0; i < nbNoVide - 1; ++i) {
            printf(" %d, ", resultat[i]);
        }
        
        printf(" %d", resultat[nbNoVide - 1]);
        printf("} \n");
    }
    
    // Libération mémoire du résultat
    free(resultat);
    resultat = 0;
    
    return 0;
}
 
