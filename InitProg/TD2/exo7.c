/* 
 * @file exo7.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 23/09/2015
 * @version 1
 * Polytech Marseille
 * Exercice 7 du TD2
 */
 
#include<stdio.h>

const int maxLine = 100;

int main() {
    int line = 0;
    
    while(line <= 0 || line >= maxLine) {
        printf("Entrer le nombre de ligne : ");
        scanf("%d", &line);
    }
    
    int i, j;
    for(i = 0; i < line + 1; ++i) {
        int nbSpace = (line - i);

        // On ajoute le nombre d'espace suffisant celon la ligne
        for(j = 0; j < nbSpace; ++j) {
            printf(" ");
        }
        
        // On ajoute la première moitié
        for(j = 0; j < line - nbSpace; ++j) {
            printf("%d", (i + j)%10);
        }
        
        // On ajoute la partie suivante
        for(j = line - nbSpace - 1 ; j > 0 ; --j) {
            printf("%d", (i + j - 1)%10);
        }
           
        printf("\n");
    }
    
    return 0;
}
 
