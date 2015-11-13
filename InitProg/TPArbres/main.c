/* 
 * @file main.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 4/11/2015
 * @version 1
 * Polytech Marseille
 * TD sur les listes et files
 * Création et parcours d'arbres
 */
 
#include <stdio.h>
#include <stdlib.h>

typedef struct t_feuille {
    char val;
    struct t_feuille* rightNode;
    struct t_feuille* leftNode; 
} t_feuille;

typedef t_feuille* t_ptr_arbre;

void cree_feuille() {

}

void val_feuille() {
}

int est_feuille(t_ptr_arbre a) {
    return a.rightNode == NULL && a.leftNode == NULL; 
}

void creer_noeud() {
}

t_feuille arbre_fg(t_feuille f) {
    return f->leftNode;
}

t_feuille arbre_fd(t_feuille f) {
    return f->rightNode;
}

char arbre_etiq(t_feuille f) {
    return f->val;
}

int main() {

    t_ptr_arbre arbre;
    return 0;
}
 
