/* 
 * @file michon_exo3.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 16/10/2015
 * @version 1
 * Polytech Marseille
 * Exercice 3 du TP d'évaluation
 * Stocke les éléments d'indice pair d'un tableau A dans un tableau B et 
 * stocke les éléments d'indice impairs du tableau A dans un tableau C
 */
 
#include <stdio.h>
#include <stdlib.h>

#define N 5

int main() {
    int A[N] = {1, 2, 3, 4, 5};
    int B[N];
    int C[N];
    int i;
    int iB = 0;
    int iC = 0;
    
    for(i = 0; i < N; ++i) {
        if(i%2 == 0) {
            B[iB] = A[i];
            iB++;
        }
        else { // Cas impair
            C[iC] = A[i];
            iC++;
        }
    }
    
// Affichage de B
    printf("B[] = { ");
    for(i = 0; i < iB-1; ++i)
        printf("%d, ", B[i]);
    printf("%d }\n", B[iB-1]);
    
// Affichage de C
    printf("C[] = { ");
    for(i = 0; i < iC-1; ++i)
        printf("%d, ", C[i]);
    printf("%d }\n", C[iC-1]);
    
    return 0;
} 
