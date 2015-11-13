/* 
 * @file michon_exo5.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 16/10/2015
 * @version 1
 * Polytech Marseille
 * Exercice 5 du TP d'évaluation
 * Affichage d'un triangle inversée
 */
 
#include <stdio.h>
#include <stdlib.h>

int main() {
    int line = 10;
    int i, j, nbSpace;
    
    for(i = line; i >= 0; --i) {
        nbSpace = (line - i);

// Ajout du nombre d'espace suffisant celon la ligne
        for(j = 0; j < nbSpace; ++j) {
            printf(" ");
        }
// Ajout de la première moitié
        for(j = 0; j < line-nbSpace; ++j) {
            printf("%d", (j+i)%10);
        }
// Ajout de la partie suivante
        for(j = line-nbSpace-1; j > 0; --j) {
            printf("%d", (i+j-1)%10);
        }
        printf("\n");
    }
    
    return 0;
} 
