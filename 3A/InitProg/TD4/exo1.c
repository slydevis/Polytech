/* 
 * @file exo1.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 06/10/2015
 * @version 1
 * Polytech Marseille
 * Exercice 1 du TD4
 * Creation de la fonction puissance qui fait x^n
 */
 
#include <stdio.h>
#include <stdlib.h>

int puissance(float x, int n) {
    float xn = 1;
   
    while(n > 0) {
        if(n%2 == 1)
            xn = xn*x;

        n = n/2;     
        x = x*x;
    }
    
    return xn;
}

int main() {
    int res = 0;
    res = puissance(2,2);
    printf("2^2 = %d\n", res);
    res = puissance(2, 0);
    printf("2^0 = %d\n", res);
    res = puissance(2, 10);
    printf("2^10 = %d\n", res);
    res = puissance(2, 1);
    printf("2^1 = %d\n", res);
    return 0;
}
 
