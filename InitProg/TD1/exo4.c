/* 
 * @file exo1.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 23/09/2015
 * @version 1
 * Polytech Marseille
 * Exercice 4 du TD1
 */
 
#include<stdio.h>

int main() {
    float prix;
    printf("Rentrer un prix : ");
    scanf("%f", &prix);
    
    printf("\nArrondi à l'euro inférieur : %d\n", (int) prix);
    printf("Arrondi à l'euro le plus proche %d\n", (int)(prix + 0.5));
    
    float quart = 4 * prix + 0.5; 
    float arrQuart = (int) quart / 4.0;
    printf("Arrondi au quart d'euro le plus proche %f\n", arrQuart);
    
    return 0;
}
