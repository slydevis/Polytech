/* 
 * @file exo1.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 23/09/2015
 * @version 1
 * Polytech Marseille
 * Exercice 6 du TD2
 */
 
#include<stdio.h>

int main() {
    int i, j, line, column;
    
    do {
        printf("Rentrer le nombre de ligne : ");
        scanf("%d", &line);
    } while(line <= 0);
    
    do {
        printf("Rentrer le nombre de colonne : ");
        scanf("%d", &column);
    } while(column <= 0);
    
    for(i = 0; i < line; ++i) {

        for(j = 0; j < column; ++j) {
            printf("(%d, %d) ", i + 1, j + 1);
        }

        printf("\n");
    }

    return 0;
}
 
