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

int finDico(int tab[], int val) {
    int beg, end, middle, found;
     
    beg = 0;
    end = N;
    found = 0;
    
    while(found == 0 && ((end - beg) > 1)) {
        middle = (beg + end)/2;
        
        if(tab[middle] == val)
            found = 1;
        
        if(tab[middle] > val)
            end = middle;
        else
            beg = middle;  
    }
  
    if(tab[beg] == val)
        return beg;
    else
        return -1;
}

int main() {
    int tab[N] = {-3, -1, 4, 5, 10, 11, 12, 13, 14, 15};
    int X;
    int pos;
    
    printf("Entrer une valeur à rechercher : ");
    scanf("%d", &X);

    pos = finDico(tab, X);
    
    if(pos >= 0)
        printf("Position trouvé = %d\n", pos);
    else
        printf("Valeur non trouvé\n");
    return 0;
}
 
