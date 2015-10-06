/* 
 * @file exo4.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 06/10/2015
 * @version 1
 * Polytech Marseille
 * Exercice 4 du TD4
 * Creer une fonction qui fait la recherche dichotomique sur un tableau
 */
 
#include <stdio.h>

int finDico(int tab[], int val, int n) {
    int beg, end, middle, found;
     
    beg = 0;
    end = n;
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
        return 1;
    else
        return 0;
}

int main() {
    int tab[N] = {-3, -1, 4, 5, 10, 11, 12, 13, 14, 15};
    int X;
    int pos;
    
    printf("Entrer une valeur à rechercher : ");
    scanf("%d", &X);

    pos = finDico(tab, X, N);
    
    if(pos >= 0)
        printf("Position trouvé = %d\n", pos);
    else
        printf("Valeur non trouvé\n");
        
    return 0;
}
