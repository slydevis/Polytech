/* 
 * @file exo1.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 23/09/2015
 * @version 1
 * Polytech Marseille
 * Exercice 7 du TD1
 */
 
 #include<stdio.h>

#define NB_BILLET 7 
int euro[NB_BILLET] = {500, 200, 20, 10, 5, 2, 1};
int cpt[NB_BILLET];

int main() {
    int somme = 0;
    printf("Entrer une somme d'argent : ");
    scanf("%d", &somme);
    
    for(int i = 0; i < NB_BILLET; ++i) {       
        while(somme%euro[i] >= 0 && somme >= euro[i]) {
            cpt[i]++;
            somme = somme - euro[i];
        }
    }

    for(int i = 0; i < NB_BILLET; ++i)
        printf("%dx%d ", euro[i], cpt[i]);
    
    printf("\n");
    return 0;
}
