/* 
 * @file exo8.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 06/10/2015
 * @version 1
 * Polytech Marseille
 * Exercice 8 du TD4
 * Calcul de la puissance avec une fonction récursive
 */
 
#include <stdio.h>
#include <stdlib.h>

int puissance(float x, int n) {
    int tmp;
    
    if (n == 0) 
        return 1;
    if (n == 1)
        return x;

    tmp = puissance(x, n / 2);
    tmp *= tmp;
    
    return (n % 2 == 0) ? tmp : tmp * x;
}

int main() {
    int res = puissance(2, 10);
    printf("res = %d\n", res);
    return 0;
}
 
