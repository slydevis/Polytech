/* 
 * @file exo6.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 29/09/2015
 * @version 1
 * Polytech Marseille
 * Exercice 6 du TD3
 * Recherche dichotomique d'un élément d'un tableaux
 */
 
#include <stdio.h>
#include <stdlib.h>

#define N 10

int finDico(int tab[], int X) {
    int beg = 0;
    int end = N - 1;
    int pos; 
    
    if(X > tab[end])
        return end;
    
    while(beg != end) {
        pos = (beg+end)/2;

        if(X < tab[pos])
            end = pos;
        else
            beg = pos+1;
    }
    
    return pos;
}

int main() {
    int tab[N] = {1, 2, 4, 5, 10, 11, 12, 13, 14, 15};
    int X;
    int pos;
    
    printf("Entrer une valeur à rechercher : ");
    scanf("%d", &X);

    pos = finDico(tab, X);
    printf("Position trouvé = %d\n", pos);
    return 0;
}
 
