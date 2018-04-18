/* 
 * @file exo1.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 23/09/2015
 * @version 1
 * Polytech Marseille
 * Exercice 3 du TD2
 */
 
#include<stdio.h>

int main() {
    int nb = 0;
    int somme = 0;
    int cpt = 0;
    
    printf("Entrer un nombre de la suite : ");
    scanf("%d", &nb);
    
    while(nb >= 0) {
        cpt++;
        somme = somme + nb;
        printf("Entrer un nombre de la suite : ");
        scanf("%d", &nb);        
    }
    
    printf("La moyenne est de : %f\n",  (float) somme/cpt);
    
    return 0;
}
 
