/* 
 * @file exo5.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 29/09/2015
 * @version 1
 * Polytech Marseille
 * Exercice 5 du TD3
 * Fusion en un tableau trié de deux tableaux trié de tailles différentes
 * On suppose qu'il n'y pas de doublon entre les deux tableaux
 */
 
#include <stdio.h>
#include <stdlib.h>

#define N 10
#define M 5

int main() {
    int A[N] = {1, 2, 3, 4, 5, 6, 7, 23, 24, 25};
    int B[M] = {11, 12, 13, 26, 27};
    const int sizeResult = N + M;
    
    int *resultat = (int*) malloc(sizeof(int)*(sizeResult));

    int i, j = 0, k = 0;    
    for(i = 0; i < sizeResult; ++i) {
        if(A[j] < B[k]) {
            resultat[i] = A[j];
            j++;
        }
        else {
            resultat[i] = B[k]; 
            k++;
        }
    }

    // Affichage du résultat    
    printf("T[] = {");
    
    for(i = 0; i < sizeResult - 1; ++i) {
        printf(" %d, ", resultat[i]);
    }
    
    printf(" %d", resultat[sizeResult - 1]);
    printf("} \n");

    // Libération de la mémoire
    free(resultat);
    resultat = NULL;
    
    return 0;
}
 
