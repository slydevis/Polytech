/* 
 * @file exo1.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 23/09/2015
 * @version 1
 * Polytech Marseille
 * Exercice 5 du TD1
 */
 
 #include<stdio.h>
 #include<math.h>
 
 // Calcule du l'équation de second degré
 void secondDeg(int a, int b, int c) {
    if(a == 0) {
        if(b == 0) {
            printf("Il y a une infinité de solution\n");
        }
        else /* b != 0 */ {
            float solution = -c/b;
            printf("Solution = %g\n", solution);   
        }
    }
    else {
        int delta = (b*b) - (4 * a * c);
        if(delta > 0) {
            float x1 = (-b + sqrt(delta)) / (2 * a);
            float x2 = (-b - sqrt(delta)) / (2 * a);
            
            printf("Solution 1 : %g\n", x1);
            printf("Solution 2 : %g\n", x2);
        }
        else if(delta == 0) {
            float x1 = (-b) / (2 * a);
            
            printf("Solution : %g\n", x1);
        }
        else {
            float imag = sqrt(- delta);
            
            printf("Solution 1 : (%d - %gi)/%d\n", -b, imag, 2*a);
            printf("Solution 2 : (%d + %gi)/%d\n", -b, imag, 2*a); 
        }
    }
 }
 
 int main() {
    int a, b, c;
    
    printf("Rentrer a : ");
    scanf("%d", &a);
    
    printf("Rentrer b : ");
    scanf("%d", &b);
    
    printf("Rentrer c : ");
    scanf("%d", &c);
    
    secondDeg(a, b, c);
       
    return 0;
}
