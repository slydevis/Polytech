/* 
 * @file exo2.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 08/10/2015
 * @version 1
 * Polytech Marseille
 * Exercice 2 du TD5
 * Tri à bulle d'un tableau non trié
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

void bubbleSort(int tab[], int n) {
    int i, j;

    for(i = 0; i < n-1; i = i+2) {
        for(j = i+1; j < N; ++j) {
            if(tab[j] < tab[j-1])
                swap(&tab[j], &tab[j-1]);
        }
        
        for(j = n-1; j > i-1; --j) {
            if(tab[j] < tab[j-1])
                swap(&tab[j], &tab[j-1]);
        }
    }
}

void afficheTab(int tab[], int n) {
    int i;
    
    printf("{ ");
    for(i = 0; i < n-1; ++i)
        printf("%d, ", tab[i]);
    
    printf("%d ", tab[n-1]);
    printf("}\n");
}
int main() {
    int tab[N] = {3, 2, 4, 8, 5, 7, 6, 1};
    bubbleSort(tab, N); 
    afficheTab(tab, N);
    return 0;
}
 
