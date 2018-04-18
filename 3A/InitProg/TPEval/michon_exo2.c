/* 
 * @file michon_exo2.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 16/10/2015
 * @version 1
 * Polytech Marseille
 * Exercice 2 du TP d'évaluation
 * Transpose une matrice A[N][M] en une matrice B[M][N]
 */
 
#include <stdio.h>
#include <stdlib.h>

#define N 5
#define M 3

int main() {
    int A[N][M];
    int B[M][N];
    int i, j;
    
// Initialisation de A
    for(i = 0; i < N; ++i)
        for(j = 0; j < M; ++j)
            A[i][j] = i+j;
            
// Affichage de A
    printf("A[][] = {\n");
    for(i = 0; i < N; ++i) {
        for(j = 0; j < M-1; ++j)
            printf("%d, ", A[i][j]);

        printf("%d", A[i][M-1]);
        printf("\n");
    }
    printf("}\n");
    
// Transposition de la matrice A dans B
    for(i = 0; i < M; ++i)
        for(j = 0; j < N; ++j)
            B[i][j] = A[j][i];

// Affichage de B
    printf("B[][] = {\n");
    for(i = 0; i < M; ++i) {
        for(j = 0; j < N-1; ++j)
            printf("%d, ", B[i][j]);

        printf("%d", B[i][N-1]);
        printf("\n");
    }
    printf("}\n");
    
    return 0;
} 
