/* 
 * @file exo2.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 06/10/2015
 * @version 1
 * Polytech Marseille
 * Exercice 2 du TD4
 * Affiche la décomposition binaire d'un entier
 */
 
#include <stdio.h>
#include <stdlib.h>

#define N 10
char res[N];

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

void decomBin(char* res, int n) {
    int i = 0;
    int power = N;
    int maxBin = puissance(2, power);
    
    while(maxBin > 1) {
        if(n > maxBin) {
            n = n - maxBin;
            res[i] = '1';
        }
        else {
            res[i] = '0';    
        }
        
        power = power - 1;
        maxBin = puissance(2, power);
        i++;
    }
    
    if(n == 1)
        res[i] = '1';
    else
        res[i] = '0';
}

int main() {
    decomBin(res, 1025);
    printf("1025 = %s\n", res);
    return 0;
}
 
