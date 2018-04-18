/* 
 * @file exo1.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 23/09/2015
 * @version 1
 * Polytech Marseille
 * Exercice 1 du TD2
 * Répétition du calcul de la TVA
 */
 
#include<stdio.h>

#define TAUX_TVA 20
#define TVA TAUX_TVA/100

int main() {
    float prixTTC = 0.0f, prixHT = 0.0f, somme = 0.0f;
    int cpt = 0;
    
    do {
        printf("Entrer un prix HT : ");
        scanf("%f", &prixHT);
        prixTTC = prixHT + prixHT*TVA;
        printf("\nLe prix TTC avec une TVA de %d est %g\n", TAUX_TVA, prixTTC);    
        ++cpt;
        somme = somme + prixTTC;
    } while(prixHT > 0);
    
    printf("Somme = %f\n", somme);
    printf("Nombre de calculs = %d\n", cpt); 
    return 0;
}
 
