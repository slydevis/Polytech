/* 
 * @file exo1.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 23/09/2015
 * @version 1
 * Polytech Marseille
 * Exercice 5 du TD2
 */
 
#include<stdio.h>

#define N 21
int tab[N] = { 0 };

int main() {
    int x = 0;
    int i;
    
    printf("Entrer un nombre : ");
    scanf("%d", &x);

    while(x >= 0 && x <= 20) {
        tab[x] = tab[x] + 1;
        printf("Entrer un nombre : ");
        scanf("%d", &x);
    }
    
    for(i = 0; i < N; ++i) {
        printf("Nombre de %d = %d\n", i, tab[i]);
    }
    
    return 0;
}
 
