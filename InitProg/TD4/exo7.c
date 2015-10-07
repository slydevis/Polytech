/* 
 * @file exo7.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 06/10/2015
 * @version 1
 * Polytech Marseille
 * Exercice 7 du TD4
 * Calcul le nombre de combinaison de p objet parmis n
 */
 
#include <stdio.h>
#include <stdlib.h>

int factoriel(int n) {
    if(n > 1)
        return n * factoriel(n - 1);
    
    return 1;
} 
int combi(int p, int n) {
    int res = 0;
    int dem = factoriel(p);
    dem = dem*factoriel(n-p);
    res = factoriel(n)/dem;
    return res;
}

int combi2(int n, int p) {
// Problème de comprehension de la formule
    int res = 1;
    int pOrigin = p;
    int tmp;
    
    while(p >= 1) {
        tmp = (n - pOrigin + p)/p;
        res = res*tmp;
        p--;
    }
    
    return res;
}

int main() {
    int res = combi(2, 3);
    printf("res = %d\n", res);
    res = combi2(2, 3);
    printf("res = %d\n", res);
    return 0;
}
 
