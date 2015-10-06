/* 
 * @file exo5.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 06/10/2015
 * @version 1
 * Polytech Marseille
 * Exercice 5 du TD4
 * Creer une fonction qui calcule le produit de deux matrices
 */
 
#include <stdio.h>

#define N 2
#define M 3

void mult(double A[N][M], double B[M][N], double C[N][N]) {
    int i;
    int j;
    int k;
    
    for(i = 0; i < N; ++i) {
        for(j = 0; j < M; ++j) {
            C[i][j] = 0;
            for(k = 0; k < M; ++k) {
                C[i][j] = C[i][j] +  A[i][k]*B[k][j];
            }
        }
    }
}

int main() {
    int i;
    int j;
    double A[N][M] = {{1, 2, 3}, {1, 2, 3}};
    double B[M][N] = {{1, 2}, {1, 2}, {1, 2}};
    double C[N][N];
    
    mult(A, B, C);
    
    for(i = 0; i < N; ++i) {
        for(j = 0; j < N; ++j)
            printf("%lf, ", C[i][j]);
        printf("\n");
    }
    
    return 0;
}
 
