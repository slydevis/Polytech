/* 
 * @file main.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 4/11/2015
 * @version 1
 * Polytech Marseille
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

// Liste pour le parcour en Largeur

typedef struct t_liste {
    t_ptr_arbre tree;
    struct t_liste* next;
} t_liste;

typedef t_liste* t_ptr_liste;

t_ptr_liste ajoutListe(t_ptr_liste l, t_ptr_arbre tree) {
    t_liste* mail = (t_liste*) malloc(sizeof(t_liste));
    t_ptr_liste tmp = l;
    mail->tree = tree;
    mail->next = NULL;
    
    if(l == NULL)
        return mail;
    
    while(tmp->next != NULL)
        tmp = tmp->next;
        
    tmp->next = mail;

    return l;
}

t_ptr_liste supprimerListe(t_ptr_liste l) {
    t_ptr_liste tmp = l;
    free(l);
    return tmp->next;
}

t_ptr_arbre getHead(t_ptr_liste l) {
    return l->tree;
}

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
    t_ptr_liste l = NULL;
    t_ptr_arbre tmp = NULL;
    
    if(tree != NULL)
         l = ajoutListe(l, tree);
   
    while(l != NULL) {
        tmp = l->tree;
        if(est_feuille(tmp))
            printf(" %d ", tmp->valFeuille);
        else
            printf(" %c ", tmp->etiquette);
        l = supprimerListe(l);

        if(tmp->rightNode != NULL)
            l = ajoutListe(l, tmp->rightNode);        
        if(tmp->leftNode != NULL)
            l = ajoutListe(l, tmp->leftNode);
    }
}

/* Exercice 5 : Quelques exercices vus en TD */

// 1. Calculer le nombre de nœuds internes de l’arbre.

int nbInternNode(t_ptr_arbre tree) {
    if(!est_feuille(tree))
        return 1 + nbInternNode(tree->rightNode) 
                 + nbInternNode(tree->leftNode);
    else
        return 0;
}

// 2. Calculer le nombre de feuilles de l’arbre.

int nbLeaf(t_ptr_arbre tree) {
    if(est_feuille(tree))
        return 1;
    return nbLeaf(tree->rightNode) + nbLeaf(tree->leftNode);
}

// 3. Calculer la hauteur de l’arbre.

int hauteur(t_ptr_arbre tree) {
    int a = 0, b = 0;
    
    if(tree->rightNode != NULL)
        a = hauteur(tree->rightNode) + 1;
    if(tree->leftNode != NULL)
        b = hauteur(tree->leftNode) + 1;
        
    if(a > b)
        return a;
    return b; 
}

// 4. En supposant que les feuilles comportent des valeurs numériques, 
// calculer la somme des valeurs des feuilles de l’arbre. 
// Le faire à l’aide des deux schémas récursifs.

int sommeFeuille(t_ptr_arbre tree) {
    if(est_feuille(tree))
        return tree->valFeuille;
    return sommeFeuille(tree->rightNode) + sommeFeuille(tree->leftNode);
}

// 5. A partir d’un arbre fourni, construire un nouvel arbre dans lequel 
// les feuilles apparaissent dans l’ordre inverse.

t_ptr_arbre inverseTree(t_ptr_arbre tree) {
    t_ptr_arbre tmp = tree->leftNode;
    tree->leftNode = tree->rightNode;
    tree->rightNode = tmp;

    if(tree->leftNode != NULL)
        inverseTree(tree->leftNode);
    if(tree->rightNode != NULL)
        inverseTree(tree->rightNode);
    return tree;
}

// 6. Imprimer l’arbre sous forme inﬁxe, préﬁxe et post-ﬁxe. Ecrire ces 
// fonctions sans optimisation des ’espaces’ entre entiers ou des paires 
// de parenthèses, puis avec l’optimisation.

void printInfixe(t_ptr_arbre tree) {
    if(est_feuille(tree)) {
        printf("%d", tree->valFeuille);
        return;    
    }
    
    printf("(");
    printInfixe(tree->rightNode);
    printf("%c", tree->etiquette);
    printInfixe(tree->leftNode);
    printf(")");
}

void printPostFixe(t_ptr_arbre tree) {
    if(est_feuille(tree)) {
        printf("%d ", tree->valFeuille);
        return;    
    }

    printPostFixe(tree->rightNode);
    printPostFixe(tree->leftNode);
    printf("%c", tree->etiquette);
}

void printPostFixeOpti(t_ptr_arbre tree) {
    if(est_feuille(tree)) {
        if(tree->valFeuille > 9)
            printf("%d ", tree->valFeuille);
        else
            printf("%d", tree->valFeuille);
        return;    
    }

    printPostFixeOpti(tree->rightNode);
    printPostFixeOpti(tree->leftNode);
    printf("%c", tree->etiquette);
}

// 7. Enumérer et imprimer tous les sous-arbres.

void printSousArbre(t_ptr_arbre arbre) {

}

/* Exercice 6 : Fibonacci */

t_ptr_arbre fibonacci(int n) {
    if(n <= 0)
        return cree_feuille(0);
    if(n == 1)
        return cree_feuille(1);
         
    return cree_noeud('+', fibonacci(n - 1), fibonacci(n - 2));
}

/* Exercice 7 : 8 dames */

int* dame = NULL;
int nbSolution = 0;

/* Fonction d'évaluation du problème des 8 dames */
int isFree(int ix, int iy)
{
    int i;
    for (i = 0; i < iy; ++i) {
        if (dame[i] == ix) // Colonne prise
            return 0;
        if(abs(dame[i]-ix) == abs(i-iy)) // Prise en diagonal   
            return 0;
    }   
    
    return 1;
}

void printSolution(int size) {
    int i;
    int j;
    
    for(i = 0; i < size; ++i) {
        for(j = 0; j < size; ++j) {
            printf("|");
            if(j == dame[i]) {
                printf("x");
            }
            else
                printf(" ");
            printf("|");
        }
        printf("\n");
    }
    
    printf("\n\n");
}

/* tries to place queen n on row n */
void backtrack(int start, int size)
{
    int i;
    if (start == size) {
        printSolution(size);
        nbSolution++;
    }

    for (i = 0; i < size; ++i) {
        if (isFree(i, start)) {
            dame[start] = i;
            backtrack (start+1, size);
        }    
    }
}

int huitDames(int n) {
    int i = 0;
    dame = malloc(sizeof(int)*n);
    nbSolution = 0;
    
    // Initialisation du tableau
    for(i = 0; i < n; ++i)
        dame[i] = 0;
    
    // Lancement de l'algorithme de backtrack
    backtrack(0, n);
    
    return nbSolution;
}

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
    t_ptr_arbre inverseRacine = NULL;
	afficherArbre(racine, 0);
	
	printf("Parcours en Profondeur : ");
	parcoursProfondeur(racine);
	printf("\nParcours en Largeur : ");
	parcoursLargeur(racine);
    printf("\nNombre de noed internes de l'arbre : %d", nbInternNode(racine));
    printf("\nNombre de feuille : %d", nbLeaf(racine));
    printf("\nHauteur de l'arbre : %d", hauteur(racine));
    printf("\nSomme des feuilles : %d", sommeFeuille(racine));
    printf("\nAffichage Infixe : ");
    printInfixe(racine);
    printf("\nAffiche Post-fixe : ");
    printPostFixe(racine);
    printf("\nAffiche Post-fixe optimisé : ");
    printPostFixeOpti(racine);
    printf("\n");
    inverseRacine = inverseTree(racine);
    printf("Inverse de (((1 + 2)*3) + (4*(5*6)) = \n");
	afficherArbre(inverseRacine, 0);
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
	printf("\nParcours en Largeur : ");
	parcoursLargeur(racine);
    printf("\nNombre de noed internes de l'arbre : %d", nbInternNode(racine));
    printf("\nNombre de feuille : %d", nbLeaf(racine));
    printf("\nHauteur de l'arbre : %d", hauteur(racine));
    printf("\nSomme des feuilles : %d", sommeFeuille(racine));
    printf("\nAffichage Infixe : ");
    printInfixe(racine);
    printf("\nAffiche Post-fixe : ");
    printPostFixe(racine);
    printf("\nAffiche Post-fixe optimisé : ");
    printPostFixeOpti(racine);
    printf("\n");
    inverseRacine = inverseTree(racine);
    printf("Inverse de (((1 + 2)*3) + (4*(5*6)) = \n");
	afficherArbre(inverseRacine, 0);
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
	printf("\nParcours en Largeur : ");
	parcoursLargeur(racine);
    printf("\nNombre de noed internes de l'arbre : %d", nbInternNode(racine));    
    printf("\nNombre de feuille : %d", nbLeaf(racine));
    printf("\nHauteur de l'arbre : %d", hauteur(racine));
    printf("\nSomme des feuilles : %d", sommeFeuille(racine));
    printf("\nAffichage Infixe : ");
    printInfixe(racine);
    printf("\nAffiche Post-fixe : ");
    printPostFixe(racine);
    printf("\nAffiche Post-fixe optimisé : ");
    printPostFixeOpti(racine);
    printf("\n");
    inverseRacine = inverseTree(racine);
    printf("Inverse de (((1 + 2)*3) + (4*(5*6)) = \n");
	afficherArbre(inverseRacine, 0);
    freeArbre(racine);
    
	printf("\nFibonacci de 3 : ");
	printInfixe(fibonacci(3));
	
	printf("\n");
	
	int nbSol = huitDames(4);
    printf("\nDame(4) : Nombre de solution = %d\n", nbSol);
	nbSol = huitDames(8);
    printf("\nDame(8) : Nombre de solution = %d\n", nbSol);
	nbSol = huitDames(10);
    printf("\nDame(10) : Nombre de solution = %d\n", nbSol);
	nbSol = huitDames(15);
    printf("\nDame(15) : Nombre de solution = %d\n", nbSol);
	return 0;
}
