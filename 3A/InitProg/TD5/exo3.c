/* 
 * @file exo3.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 08/10/2015
 * @version 1
 * Polytech Marseille
 * Exercice 3 du TD5
 * Tri à bulle d'un tableau non trié
 */
 
#include <stdio.h>
#include <stdlib.h>

#define N 8

const int h0 = 5; // Choisi arbitrairement

void swap(int* a, int* b) {
    int c;
    c = *a;
    *a = *b;
    *b = c;
}

void shellSort(int tab[], int n) {
    int h, i, j;
    
    for(h = h0; h >= 1; h = h/2) {
        for(i = h; i < n; ++i) {
            j = i;
            if(j == h && tab[j-h] > tab[j])
               swap(&tab[j], &tab[j-h]);
                
            while(j > h && tab[j-h] > tab[j]) {
                swap(&tab[j], &tab[j-h]);
                j = j-h;
            }
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
    shellSort(tab, N); 
    afficheTab(tab, N);
    return 0;
}
 
