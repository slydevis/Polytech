/* 
 * @file exo1.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 23/09/2015
 * @version 1
 * Polytech Marseille
 * Exercice 2 du TD1
 */
 
#include<stdio.h>

#define TAUX_TVA 20
float TVA = (float) TAUX_TVA/100.0;

int main() {
    float prixTTC = 0, prixHT = 0;
    printf("Entrer un prix TTC : ");
    scanf("%f", &prixTTC);
    prixHT = prixTTC / (TVA + 1.0);
    printf("prixHT = %f avec une TVA de %f\n", prixHT, prixTTC - prixHT);
    return 0;
}
 
