/* 
 * @file exo1.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 23/09/2015
 * @version 1
 * Polytech Marseille
 * Exercice 8 du TD2
 * Somme des colonnes et des lignes
 */
 
#include<stdio.h>

#define MAX_LINES 3
#define MAX_COLUMN 4

float T[MAX_LINES + 1][MAX_COLUMN + 1];

void initArray() {
    int i, j;
    for(i = 0; i < MAX_LINES + 1; ++i) {
        for(j = 0; j < MAX_COLUMN + 1; ++j) {
            T[i][j] = 0.0f;
        }
    }
}
void updateValue() {
    // Line result update
    int i, j, somme;
    for(i = 0; i < MAX_LINES; ++i) {
        somme = 0.0f;
        for(j = 0; j < MAX_COLUMN; ++j) {
            somme = somme + T[i][j];
            T[i][MAX_COLUMN] = somme;
        }
    }
    
    // Column result uptade
    for(j = 0; j < MAX_COLUMN; ++j) {
        somme = 0.0f;
        for(i = 0; i < MAX_LINES; ++i) {
            somme = somme + T[i][j];
            T[MAX_LINES][j] = somme;
        }
    }
}

void printArray() {
    int i, j;
    
    // Print array
    for(i = 0; i < MAX_LINES; ++i) {
        printf("\n");
        for(j = 0; j < MAX_COLUMN; ++j) {
            printf(" %g ", T[i][j]);
        }
        
        // Print line result
        printf("|");
        printf(" %g ", T[i][MAX_COLUMN]);
    }
    
    printf("\n");
    
    // Print column result border
    for(i = 0; i < MAX_COLUMN + 1; ++i) {
         printf("___");        
    }
    
    printf("\n");
    for(i = 0; i < MAX_COLUMN + 1; ++i) {
        if(i == MAX_COLUMN)
            printf("|");
            
       printf(" %g ", T[MAX_LINES][i]);
    }
   
    printf("\n");
}

int main() {
    initArray();
    printArray();
    
    int i, j;
    float x;
    
    do {
        updateValue();
        printArray();            
        printf("Entrer i : ");
        scanf("%d", &i);
        printf("Entrer j : ");
        scanf("%d", &j);
        printf("Entrer x : ");
        scanf("%f", &x);
        
        if(i >= 0 && i < MAX_LINES) {
            if(j >= 0 && j < MAX_LINES) {
                T[i - 1][j - 1] = x;
            }
        }
        
    } while(i >= 0);

    return 0;
}
 
