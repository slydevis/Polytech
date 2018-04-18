/* 
 * @file exo1.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 23/09/2015
 * @version 1
 * Polytech Marseille
 * Exercice 1 du TD1
 */
 
#include<stdio.h>

#define TAUX_TVA 20
#define TVA TAUX_TVA/100

int main() {
    float prixTTC = 0, prixHT = 0;
    printf("Entrer un prix HT : ");
    scanf("%f", &prixHT);
    prixTTC = prixHT + prixHT*TVA;
    printf("\nLe prix TTC avec une TVA de %d est %g\n", TAUX_TVA, prixTTC);
    return 0;
}
 
