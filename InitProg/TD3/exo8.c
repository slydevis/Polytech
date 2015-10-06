/* 
 * @file exo8.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 29/09/2015
 * @version 1
 * Polytech Marseille
 * Exercice 8 du TD3
 * Affiche la n-ième ligne du triangle de pascal
 */
 
#include <stdio.h>
#include <stdlib.h>

#define N 7

int tab[N*N];

int main() {
    int indice;
    int i = 0;
    int j = 0;
    int x = 0;
    
    // Initialisation du tableau à 1
    for(i = 0; i < N; ++i) {
        for(j = 0; j < N; ++j) {
            indice = i + j*N;
            tab[indice] = 1;            
        }
    }
    
    // Mise à jours des valeurs
    tab[0] = 1;
    for(i = 1; i < N; ++i) {
        tab[i] = 1;
        for(j = 1; j < i -1; ++j) {
            indice = i + j*N;
            tab[indice] = tab[i-1 + (j-1)*N] + tab[i -1 + j*N];
        }
        
        indice = i + j*N;
        tab[indice] = 1;
    }
  
    printf("Entrer la ligne a afficher : ");
    scanf("%d", &x);
      
    for(i = 0; i - 1 <= x && i < N; ++i) {
        if(i - 1 == x) {
            for(j = 0; j < i; ++j) {
                indice = i + j*N;
                printf("%d ", tab[i + j*N]);
            }
        }
    }
    
    printf("\n");
    return 0;
}
 
