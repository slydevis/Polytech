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

void freeArbre(t_ptr_arbre tree) {
    if(tree)
        return;
    freeArbre(tree->rightNode);
    freeArbre(tree->leftNode);
    free(tree);
}

/* Exercice 3 : Parcours en profondeur */

void parcoursProfondeur(t_ptr_arbre tree) {
    if(tree == NULL)
        return;
        
    if(est_feuille(tree))
        printf(" %d ", tree->valFeuille);
    else
        printf(" %c ", tree->etiquette);
   
    parcoursProfondeur(tree->rightNode);      
    parcoursProfondeur(tree->leftNode);
}

/* Exercice 4 : Parcours en largeur */

void parcoursLargeur(t_ptr_arbre tree) {
    
}

/* Exercice 5 : Quelques exercices vus en TD */

/* Exercice 6 : Fibonacci */

/* Exercice 7 : 8 dames */

int main() {
	/* Exercice 2 : Trois arbres */
	// (((1 + 2)*3) + (4*(5*6)))
	printf("# (((1 + 2)*3) + (4*(5*6))) = \n");
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
	
	printf("Parcours en Profondeur : ");
	parcoursProfondeur(racine);
	printf("\nParcours en largeur : ");
	parcoursLargeur(racine);
    printf("\n");
	freeArbre(racine);
	// ((((1 + 2) + 3) + 4) + (((5*6) + 7)))
	printf("# ((((1 + 2) + 3) + 4) + (((5*6) + 7))) = \n");
    un = cree_feuille(1);
    deux = cree_feuille(2);
    plus = cree_noeud('+', un, deux);
    trois = cree_feuille(3);
    t_ptr_arbre unPlusDeuxPlusTrois = cree_noeud('+', plus, trois);    
    quatre = cree_feuille(4);
    t_ptr_arbre unPlusDeuxPlusTroisPlusQuatre = cree_noeud('+', unPlusDeuxPlusTrois, quatre);
    cinq = cree_feuille(5);
    six = cree_feuille(6);
    cinqFoisSix = cree_noeud('*', cinq, six);
    t_ptr_arbre sept = cree_feuille(7);
    t_ptr_arbre cinqFoisSixPlusSept = cree_noeud('+', cinqFoisSix, sept);
    racine = cree_noeud('+', unPlusDeuxPlusTroisPlusQuatre, cinqFoisSixPlusSept);
    afficherArbre(racine, 0);
	printf("Parcours en Profondeur : ");
	parcoursProfondeur(racine);
	printf("\nParcours en largeur : ");
	parcoursLargeur(racine);
    printf("\n");
    freeArbre(racine);
    
	// ((1 + (2*(3 + 4))) * (5 + 6)*(7+(8*9))))
	printf("# ((1 + (2*(3 + 4))) * (5 + 6)*(7+(8*9)))) = \n");
    un = cree_feuille(1);
    deux = cree_feuille(2);
    trois = cree_feuille(3);
    quatre = cree_feuille(4);
    t_ptr_arbre troisPlusQuatre = cree_noeud('+', trois, quatre);
    t_ptr_arbre deuxFoisTroisPlusQuatre = cree_noeud('*', deux, troisPlusQuatre);
    t_ptr_arbre unPlusDeuxFoisTroisPlusQuatre = cree_noeud('+', un, deuxFoisTroisPlusQuatre);
    cinq = cree_feuille(5);
    six = cree_feuille(6);
    t_ptr_arbre cinqPlusSix = cree_noeud('+', cinq, six);
    sept = cree_feuille(7);
    t_ptr_arbre huit = cree_feuille(8);
    t_ptr_arbre neuf = cree_feuille(9);
    t_ptr_arbre huitFoisNeuf = cree_noeud('*', huit, neuf);
    t_ptr_arbre septPlusHuitFoisNeuf = cree_noeud('+', sept, huitFoisNeuf);
    t_ptr_arbre cinqPlusSixFoisSeptPlusHuitFoisNeuf = cree_noeud('*', cinqPlusSix, septPlusHuitFoisNeuf); 
    racine = cree_noeud('*', unPlusDeuxFoisTroisPlusQuatre, cinqPlusSixFoisSeptPlusHuitFoisNeuf);
    afficherArbre(racine, 0);
 	printf("Parcours en Profondeur : ");
	parcoursProfondeur(racine);
	printf("\nParcours en largeur : ");
	parcoursLargeur(racine);
    printf("\n");
    freeArbre(racine);
    
	return 0;
}
