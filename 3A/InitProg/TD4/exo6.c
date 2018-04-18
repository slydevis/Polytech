/* 
 * @file exo6.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 06/10/2015
 * @version 1
 * Polytech Marseille
 * Exercice 6 du TD4
 * Concatène deux chaines de charactère entre elles
 */
 
#include <stdio.h>
#include <stdlib.h>
 
void my_strcat(char* s1, char* s2) {
    while(*s1 != '\0')
        s1++;
    
    while(*s2 != '\0') {
        *s1 = *s2;
        s2++;
        s1++;
    }
    
    *s1 = '\0';
}

int main() {
    char s1[] = "toto";
    char s2[] = "tutu";

    my_strcat(s1, s2);
    
    printf("s1 = %s\n", s1);
    
    return 0;
}
 
