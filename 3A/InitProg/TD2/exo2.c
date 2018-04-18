/* 
 * @file exo1.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 23/09/2015
 * @version 1
 * Polytech Marseille
 * Exercice 2 du TD2
 */
 
#include<stdio.h>
#include<math.h>

int main() {
    float deg, degRad, sinus;    
    float p = 0.0f, start, end;
    
    while(p <= 0.0f) {
        printf("Entrer le pas : ");
        scanf("%f", &p);
    }
    
    do {
        printf("Entrer le début : ");
        scanf("%f", &start);
        printf("Entrer la fin : ");
        scanf("%f", &end);
    } while(start > 0 && (start - end) > 0 && end < 360);
    
 
    for(deg = start; deg <= end; deg = deg + p) {
        degRad = deg * acos(-1)/180;
        sinus = sin(degRad);
        printf("sin(%g) = %f\n", deg, sinus);
    }
        
    return 0;
}
 
