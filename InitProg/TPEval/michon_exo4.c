/* 
 * @file michon_exo4.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 16/10/2015
 * @version 1
 * Polytech Marseille
 * Exercice 4 du TP d'évaluation
 * Création et affichage d'un triangle de pascal
 */
 
#include <stdio.h>
#include <stdlib.h>

#define N 6

// Calcul du nombre de combinaison de n parmis p 
// en paramètre n > p > 0 
int combinaison(int n, int p) {
    if(p == 0 || p == n)
        return 1;
    if(0 < p && p < n)
        return combinaison(n-1, p-1) + combinaison(n-1, p);
    return 0;
}

// Initialise une matrice C de taille N en paramètre avec les valeau d'un
// triangle de pascal on rempli les cases vides à 0
void pascal(int C[N][N]) {
    int i, j;
    for(i = 0; i < N; ++i)
        for(j = 0; j < N; ++j)
            C[i][j] = combinaison(i, j);
}

int main() {
    int i, j;
    int C[N][N];    
    pascal(C);
    
// Affichage du résultat
    for(i = 0; i < N; ++i) {
        for(j = 0; j < N; ++j) {
            if(C[i][j] != 0)
                printf("%d ", C[i][j]);
        }
        printf("\n");
    }
    
    return 0;
} 
