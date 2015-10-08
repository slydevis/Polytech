/* 
 * @file exo1.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 08/10/2015
 * @version 1
 * Polytech Marseille
 * Exercice 1 du TD5
 * Tri par sélection et échange d'un tableau non trié
 */
 
#include <stdio.h>
#include <stdlib.h>

#define N 8

void swap(int* a, int* b) {
    int c;
    c = *a;
    *a = *b;
    *b = c;
}

void swapSort(int tab[], int n) {
    int indiceMin;
    int i, j;

    for(i = 0; i < n - 1; ++i) {
        indiceMin = i;
        for(j = i + 1; j < n; ++j) {
            if(tab[j] < tab[indiceMin])
                indiceMin = j;
        }
        
        swap(&tab[i], &tab[indiceMin]);
    }
}

void afficheTab(int tab[], int n) {
    int i;
    
    printf("{ ");
    for(i = 0; i < n - 1; ++i)
        printf("%d, ", tab[i]);
    
    printf("%d ", tab[n - 1]);
    printf("}\n");
}
int main() {
    int tab[N] = {2, 3, 4, 5, 6, 7, 8, 1};
    swapSort(tab, N); 
    afficheTab(tab, N);
    return 0;
}
 
