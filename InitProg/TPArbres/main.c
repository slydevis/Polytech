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

/* Exercice 1 : ADT - Abstract Data Type */

typedef struct t_noeud {
	char etiquette;
	struct t_noeud* rightNode;
	struct t_noeud* leftNode;
	int valFeuille;
} t_noeud;

typedef t_noeud* t_ptr_arbre;

t_ptr_arbre cree_feuille(int value) {
	t_ptr_arbre tmp = (t_noeud*) malloc(sizeof(t_noeud));
	tmp->valFeuille = value;
	tmp->rightNode = NULL;
	tmp->leftNode = NULL;
	tmp->etiquette = ' ';
	return tmp;
}

int val_feuille(t_ptr_arbre f) {
	if(f->rightNode == NULL && f->leftNode == NULL)
		return f->valFeuille;
	else
		return 0;
}

int est_feuille(t_ptr_arbre a) {
	return (a->leftNode == NULL && a->rightNode == NULL);
}

t_ptr_arbre cree_noeud(char etiq, t_ptr_arbre right, t_ptr_arbre left) {
	t_ptr_arbre tmp = (t_noeud*) malloc(sizeof(t_noeud));
	tmp->etiquette = etiq;
	tmp->rightNode = right;
	tmp->leftNode = left;
	tmp->valFeuille = 0;
	return tmp;
}

t_ptr_arbre arbre_fg(t_ptr_arbre a) {
	if(est_feuille(a))
		return NULL;
	return a->leftNode;
}

t_ptr_arbre arbre_fd(t_ptr_arbre a) {
	if(est_feuille(a))
		return NULL;
	return a->rightNode;
}

char arbre_etiq(t_ptr_arbre a) {
	if(est_feuille(a))
		return ' ';
	return a->etiquette;
}

void afficherArbre(t_ptr_arbre racine, int level) {
	int i;
	if (racine) {
		afficherArbre(racine->leftNode, level + 1);
		for (i = 0; i < level; i++) {
		printf("    ");
	}
	if(est_feuille(racine))
		printf("%d\n", racine->valFeuille);
	else
		printf("%c\n", racine->etiquette);
		afficherArbre(racine->rightNode, level + 1);
	} 
}

/* Exercice 3 : Parcours en profondeur */

void parcoursProfondeur();

/* Exercice 4 : Parcours en largeur */

void parcoursLargeur();

/* Exercice 5 : Quelques exercices vus en TD */

/* Exercice 6 : Fibonacci */

/* Exercice 7 : 8 dames */

int main() {
	/* Exercice 2 : Trois arbres */
	// (((1 + 2)*3) + (4*(5*6)))
	t_ptr_arbre un = cree_feuille(1);
	t_ptr_arbre deux = cree_feuille(2);
	t_ptr_arbre plus = cree_noeud('+', un, deux);
	t_ptr_arbre trois = cree_feuille(3);
	t_ptr_arbre unPlusDeuxFoisTrois = cree_noeud('*', plus, trois);
	t_ptr_arbre quatre = cree_feuille(4);
	t_ptr_arbre cinq = cree_feuille(5);
	t_ptr_arbre six = cree_feuille(6);
	t_ptr_arbre cinqFoisSix = cree_noeud('*', cinq, six);
	t_ptr_arbre quatreFoisCinqFoisSix = cree_noeud('*', quatre, cinqFoisSix);
	t_ptr_arbre racine = cree_noeud('+', unPlusDeuxFoisTrois, quatreFoisCinqFoisSix);

	afficherArbre(racine, 0);
	// ((((1 + 2) + 3) + 4) + (((5*6) + 7)))
	// ((1 + (2*(3 + 4))) * (5 + 6)*(7+(8*9))))
	return 0;
}