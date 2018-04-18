/* 
 * @file michon_exo1.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 16/10/2015
 * @version 1
 * Polytech Marseille
 * Exercice 1 du TP d'évaluation
 * Lecture d'une suite de nombre entier au clavier et calcule la plus
 * grande valeur de la série
 */
 
#include <stdio.h>
#include <stdlib.h>

int main() {
    int maxVal = 0;
    int val;
    
    do {
        printf("Entrer un nombre entier : ");
        scanf("%d", &val);
        if(val > maxVal)
            maxVal = val;
    } while(val >= 0);

    printf("Le nombre maximum de la suite est %d\n", maxVal);    
    return 0;
} 
