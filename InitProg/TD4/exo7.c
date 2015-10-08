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
    int Cnp = 0;
    int denominateur = factoriel(p);
    denominateur = denominateur*factoriel(n-p);
    Cnp = factoriel(n)/denominateur;
    return Cnp;
}

int combi2(int p, int n) {
    int i, k, Cnp;
    k = n-p+1;
    Cnp = 1;

    for(i = 1; i <= p; ++i)
        Cnp = (Cnp*(k++))/i;
    
    return Cnp;
}

int main() {
    int res = combi(2, 3);
    printf("res = %d\n", res);
    res = combi2(2, 3);
    printf("res = %d\n", res);
    return 0;
}
 
