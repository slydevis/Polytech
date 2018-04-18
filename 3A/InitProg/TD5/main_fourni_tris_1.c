/* 
 * @file main_fourni_tris_1.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 08/10/2015
 * @version 1
 * Polytech Marseille
 * Exercice du TD5
 * Creation de divers tri pour un tableau non trié
 */
 
#include <stdio.h>
#include <stdlib.h>

#define N 8

const int h0 = 5; // Choisi arbitrairement

/*
    Fonctions utiles
*/
void swap(int* a, int* b) {
    int c;
    c = *a;
    *a = *b;
    *b = c;
}

void afficheTab(int tab[], int n) {
    int i;
    
    printf("{ ");
    for(i = 0; i < n-1; ++i)
        printf("%d, ", tab[i]);
    
    printf("%d ", tab[n-1]);
    printf("}\n");
}

void initTab(int tab[], int n) {
    tab[0] = 3;
    tab[1] = 2;
    tab[2] = 4;
    tab[3] = 8; 
    tab[4] = 5;
    tab[5] = 7;
    tab[6] = 6;
    tab[7] = 1;
    printf("Le tableau initial durant ces test est : \n");
    afficheTab(tab, n);
}

/*
    Fonctions de tri
*/
void tri_insertion(int tab[], int n) {
    int i, j;

    for(i = 1; i < n; ++i) {
        j = i;

        while(tab[j-1] > tab[j]) {
            swap(&tab[j], &tab[j-1]);
            j = j-1;
        }
    }
}

void tri_bublle(int tab[], int n) {
    int i, j;
    
    for(i = 0; i < n-1; i++) {
        for(j = n-1; j > 0; --j) {
            if(tab[j] < tab[j-1])
                swap(&tab[j], &tab[j-1]);
        }
    }
}

void tri_bubble_opt(int tab[], int n) {
    int i, j;
    
    for(i = 0; i < n-1; i++) {
        for(j = n-1; j > i-1; --j) {
            if(tab[j] < tab[j-1])
                swap(&tab[j], &tab[j-1]);
        }
    }
}

void tri_shaker(int tab[], int n) {
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

void tri_echange(int tab[], int n) {
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

void tri_shell(int tab[], int n) {
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

int main() {
    int tab[N];
    
    printf("Tri insertion :\n");
    initTab(tab, N);
    tri_insertion(tab, N);
    printf("Apres le tri :\n");
    afficheTab(tab, N);
    
    printf("Tri Bubble :\n");
    initTab(tab, N);
    tri_bublle(tab, N);
    printf("Apres le tri :\n");
    afficheTab(tab, N);

    printf("Tri Shaker :\n");
    initTab(tab, N); 
    tri_shaker(tab, N);
    printf("Apres le tri :\n");
    afficheTab(tab, N);
    
    printf("Tri Echange :\n");
    initTab(tab, N);
    tri_echange(tab, N);
    printf("Apres le tri :\n");
    afficheTab(tab, N);
    
    printf("Tri Shell :\n");
    initTab(tab, N);
    tri_shell(tab, N);
    printf("Apres le tri :\n");
    afficheTab(tab, N);
    
    printf("Tri Bubble opt  :\n");
    initTab(tab, N);
    tri_bubble_opt(tab, N);
    printf("Apres le tri :\n");
    afficheTab(tab, N);
    return 0;
}
 
