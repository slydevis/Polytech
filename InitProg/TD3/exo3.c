/* 
 * @file exo3.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 29/09/2015
 * @version 1
 * Polytech Marseille
 * Exercice 3 du TD3
 * Pour un tableau de taille N, le programme suivant doit trouver le plus 
 * petit indice où T[i] = X ou X choisi par l'utlisateur
 */
 
#include<stdio.h>

#define N 10

int main() {    
    int T[N] = {1, 2, 3, 4, 5, 6, 3, 8, 9, 10};
    int X, i;
    
    int indice = -1; // Vaut -1 si aucun élément trouvé
    
    printf("Entrer un entier X : ");
    scanf("%d", &X);
    
    for(i = 0; i < N; ++i) {
        if(T[i] == X && indice == -1) {
            indice = i;
        }
    }
    
    if(indice == -1) {
        printf("Aucun élément on été trouvé\n");
    }
    else {
        printf("X à été trouvé à l'indice %d\n", indice);
    }
    
    return 0;
}
 
