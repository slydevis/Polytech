/* 
 * @file michon_exo6.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 16/10/2015
 * @version 1
 * Polytech Marseille
 * Exercice 6 du TP d'évaluation
 * Calcule et affiche la suite de Syracuse défini par :
 * { si n = 1 => terminé
 *   si n est pair => n <- n/2
 *   si n est impair => n <- 3n+1 }
 */
 
#include <stdio.h>
#include <stdlib.h>

// Calcule la suite de syracuse a partir de l'entier passé en paramètre
// Celui-ci doit être positif et supérieur à 0
int syracuse(int n) {
    printf("%d ", n);
    if(n == 1) {
        printf("\n");
        return 0;
    }
    
    if(n%2 == 0)
        return syracuse(n/2);
    
    return syracuse(3*n+1);
}

int main() {
    int val;
    do {
        printf("Entrer n : ");
        scanf("%d", &val);
        if(val > 0)
            syracuse(val);
    } while(val > 0);
    
    return 0;
} 
