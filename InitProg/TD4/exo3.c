/* 
 * @file exo3.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 06/10/2015
 * @version 1
 * Polytech Marseille
 * Exercice 3 du TD4
 * Creer la fonction swap qui echange le contenu de deux variables
 */
 
#include <stdio.h>

void swap(int* a, int* b) {
    int c;
    c = *a;
    *a = *b;
    *b = c;
}

int main() {
    int a = 5;
    int b = 6;
    
    swap(&a, &b);
    
    printf("a = %d, b = %d\n", a, b);
    return 0;
}
 
