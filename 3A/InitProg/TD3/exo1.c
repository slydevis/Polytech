/* 
 * @file exo1.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 29/09/2015
 * @version 1
 * Polytech Marseille
 * Exercice 1 du TD3
 * Soit deux tableau A et B le programme suivant calcule le nombre de cas
 * où A[i] = B[i]
 */
 
#include<stdio.h>

#define N 10

int main() {
    int cpt = 0;
    int i;
    
    int A[N] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    int B[N] = {2, 2, 3, 3, 3, 3, 3, 3, 9, 15};
   
    for(i = 0; i < N; ++i) {
        if(A[i] == B[i])
            cpt++;
    }
    
    // Dans les tests suivant il doit être égal à 3
    printf("Nombre de case égaux : %d\n", cpt);

    return 0;
}
 
