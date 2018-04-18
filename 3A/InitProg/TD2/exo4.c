/* 
 * @file exo1.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 23/09/2015
 * @version 1
 * Polytech Marseille
 * Exercice 4 du TD2
 */
 
#include<stdio.h>

#define N 100
int tab[N] = { 0 };

int main() {
    int i, cpt = 0;
    int x = 0;
    
    printf("Rentrer un nombre : ");
    scanf("%d", &x);
    
    while(x >= 0) {
        tab[cpt] = x;
        cpt++;
        printf("Rentrer un nombre : ");
        scanf("%d", &x);
    }

    for(i = cpt - 1; i >= 0; --i) {
        printf("%d\n", tab[i]);
    }  

    return 0;
}
 
