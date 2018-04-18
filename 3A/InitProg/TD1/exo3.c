/* 
 * @file exo1.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 23/09/2015
 * @version 1
 * Polytech Marseille
 * Exercice 3 du TD1
 */
 
#include<stdio.h>
#include<math.h>

int main() {
    float a, b;
    float A, G;
    
    printf("Rentrer a : ");
    scanf("%f", &a);
    
    printf("Rentrer b : ");
    scanf("%f", &b);
 
    A = (a + b)/2.0;
    G = (float) sqrt(a * b);
    
    printf("A = %f\n", A);
    printf("G = %f\n", G);
    
    printf("A - G = %f\n", A - G);
    return 0;
}
