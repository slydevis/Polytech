/* 
 * @file exo9.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 06/10/2015
 * @version 1
 * Polytech Marseille
 * Exercice 9 du TD4
 * Calcul du nombre de combinaison avec une fonction récursive
 */
 
#include <stdio.h>
#include <stdlib.h>

int comb(int p, int n) {
    if(p == 0 || p == n)
        return 1;
    else if(0 < p && p < n)
        return comb(p-1, n-1) + comb(p, n-1);
    return 0;
}

int main() {
    int res = comb(2, 3);
    printf("res = %d\n", res);
    return 0;
}
 
