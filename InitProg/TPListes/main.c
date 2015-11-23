/* 
 * @file main.c
 * @author Michon Guillaume <guillaume.michon@etu.univ-amu.fr>
 * @date 21/10/2015
 * @version 1
 * Polytech Marseille
 * TD sur les listes et files
 * Création et gesion d'une liste chainée
 */
 
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

/* EXERCICE 1 : ADT - Abstract Data Type */

typedef struct maillon {
    int value;
    struct maillon* next; 
} maillon;

typedef maillon* t_ptr_liste;

t_ptr_liste creer_vide() { 
    return NULL; 
}

int est_vide(t_ptr_liste ptr) {
    return ptr == creer_vide();
}

t_ptr_liste ajout_liste(t_ptr_liste liste, int val) {
    maillon* mail = (maillon*) malloc(sizeof(maillon));
    mail->value = val;
    mail->next = creer_vide();
    
    if(est_vide(liste))
        return mail;
        
    mail->next = liste;

    return mail;
}

t_ptr_liste tete_liste(t_ptr_liste liste) { 
    return liste;
}

t_ptr_liste queue_liste(t_ptr_liste liste) {
    return liste->next;
}

/* EXERCICE 2 : Création d'une liste */

t_ptr_liste creationListe() {
    int valToAdd = 0;
    t_ptr_liste liste = NULL;
    
    while(valToAdd >= 0) {
        printf("Taper un nombre entier : ");
        scanf("%d", &valToAdd);
        
        if(valToAdd >= 0)
            liste = ajout_liste(liste, valToAdd);
    }
    
    return liste;
}

t_ptr_liste creationListeADT() {
    int valToAdd = 0;
    t_ptr_liste liste = creer_vide();

    while(valToAdd >= 0) {
        printf("Taper un nombre entier : ");
        scanf("%d", &valToAdd);
        
        if(valToAdd >= 0)
            liste = ajout_liste(liste, valToAdd);
    }
    
    return liste;
}

/* EXERCICE 3 : Affichage d'une liste */

void afficher(t_ptr_liste liste) {
    if(est_vide(liste)) {
        printf("NULL\n");    
        return;
    }
    
    printf("%d, ", liste->value);
    return afficher(liste->next);
}

/* EXERCICE 4 : Longeur de liste */

int sizeList(t_ptr_liste liste) {
    if(liste == NULL)
        return 0;
    return 1 + sizeList(liste->next);
}

int sizeListADT(t_ptr_liste liste) {
    if(est_vide(liste))
        return 0;
    return 1 + sizeList(queue_liste(liste));
}

/* EXERCICE 5 : Copie de liste */

t_ptr_liste copyList(t_ptr_liste liste) {
    t_ptr_liste tmp = liste;
    t_ptr_liste newList = NULL;
    
    while(tmp != NULL) {
        newList = ajout_liste(newList, tmp->value);
        tmp = tmp->next;
    }
    
    return newList;   
}

t_ptr_liste copyListADT(t_ptr_liste liste) {
    t_ptr_liste tmp = liste;
    t_ptr_liste newList = creer_vide();
    
    while(!est_vide(tmp)) {
        newList = ajout_liste(newList, tmp->value);
        tmp = queue_liste(tmp);
    }
    
    return newList;  
}

/* EXERCICE 6 : Recherche d'un élément dans une liste */

int findListe(t_ptr_liste liste, int val) {
    int pos = 0, trouve = 0;
    t_ptr_liste tmp = liste;
    
    while(!est_vide(tmp) && trouve == 0) {
        if(tmp->value == val)
            trouve = 1;
        else {
            tmp = tmp->next;
            pos++;
        }
    }
    
    if(trouve == 0)
        pos = -1;
        
    return pos; 
}

/* EXERCICE 7 : Suppression d'un élément d'une liste */

t_ptr_liste delElem(t_ptr_liste liste, int val) {
    if(liste == NULL)
        return NULL;
    
    if(liste->value == val) {
        t_ptr_liste tmp = liste->next;
        free(liste);
        tmp = delElem(tmp, val);
        return tmp;
    }
    else {
        liste->next = delElem(liste->next, val);
        return liste;
    }    
}

/* EXERCICE 8 : Insertion dans une liste oredonnée */

t_ptr_liste addOrd(t_ptr_liste liste, int val) {
    maillon* mail = (maillon*) malloc(sizeof(maillon));
    t_ptr_liste tmp = liste;
    t_ptr_liste buff = NULL;
    
    mail->value = val;
    mail->next = NULL;
    
    if(liste == NULL)
        return mail;

    while(tmp != NULL && tmp->value < val) {
        buff = tmp;
        tmp = tmp->next;
    }
    
    mail->next = tmp;
    
    if(buff != NULL)
        buff->next = mail;
    else
        liste = mail;
    return liste;
}

t_ptr_liste creationListeOrdonne() {
    int valToAdd = 0;
    t_ptr_liste liste = NULL;
    
    while(valToAdd >= 0) {
        printf("Taper une nombre entier : ");
        scanf("%d", &valToAdd);
        
        if(valToAdd >= 0)
            liste = addOrd(liste, valToAdd);
    }
    
    return liste;
}

/* EXERCICE 9 : Inverse d'une liste */

t_ptr_liste inversionListe(t_ptr_liste liste) { 
    t_ptr_liste tmp = liste;
    t_ptr_liste buff = NULL;
    t_ptr_liste prec = NULL;
    
    while(tmp != NULL) {
        prec = tmp;
        tmp = tmp->next;
        prec->next = buff;
        buff = prec;
    }
    
    return buff;
}

t_ptr_liste inversionListeADT(t_ptr_liste liste) {
    t_ptr_liste tmp = liste;
    t_ptr_liste buff = creer_vide();
    t_ptr_liste prec = creer_vide();
    
    while(!est_vide(tmp)) {
        prec = tmp;
        tmp = queue_liste(tmp);
        prec->next = buff;
        buff = prec;
    }
    
    return buff;
}

/* TP LISTE SUITE */

/* Exercice 1 : Une liste palindrome */

/* Renvoi 1 si c'est un palindrome, 0 dans les autres cas */
int isPalindrome(t_ptr_liste liste) {
    int res = 1;
    int med = sizeList(liste);
    int cpt;
    int i;
    t_ptr_liste tmp = liste;
    t_ptr_liste debutListe = liste;

    if(med%2 == 0)
        med = med/2;
    else
        med = (med+1)/2;

    cpt = med-1;
    for(i = 0; i < med; ++i)
        tmp = tmp->next;

    while(tmp != NULL && res == 1) {
        for(i = 0; i < cpt-1; ++i)
            debutListe = debutListe->next;
    
        if(tmp->value != debutListe->value)
            res = 0;
        tmp = tmp->next;
        debutListe = liste;

        cpt = cpt - 1;
    }

    return res;
}

/* Exercice 2 : Une liste de Fibonacci */

int fib(int n) {
    if(n == 0)
        return 0;
    else if(n == 1)
        return 1;

    return fib(n-1) + fib(n-2);
}

/* Renvoie 1 si la liste est une liste de Fibonacci 0 sinon */
int isFibonnacciList(t_ptr_liste liste) {
    int i = 0, res = 1;
    t_ptr_liste tmp = liste;

    while(tmp != NULL && res == 1) {
        if(tmp->value != fib(i))            
            res = 0;

        tmp = tmp->next;
        i = i+1;
    }

    return res;
}

/* Exercice 3 : La fusion de deux liste triées */
t_ptr_liste fusionList(t_ptr_liste liste, t_ptr_liste secondList) {
    t_ptr_liste res = NULL;
    t_ptr_liste listeTmp = liste;
    t_ptr_liste secondListTmp = secondList;

    while(listeTmp != NULL) {
        res = addOrd(res, listeTmp->value);
        listeTmp = listeTmp->next;        
    }

    while(secondListTmp != NULL) {
        res = addOrd(res, secondListTmp->value);
        secondListTmp = secondListTmp->next;
    }

    return res;
}

/* Exercice 4 : La fusion de deux liste triées sans répétition */
t_ptr_liste fusionListNoRepeat(t_ptr_liste liste, t_ptr_liste secondList) {
    t_ptr_liste res = NULL;
    t_ptr_liste listeTmp = liste;
    t_ptr_liste secondListTmp = secondList;

    while(listeTmp != NULL) {
        if(findListe(res, listeTmp->value) == -1) {
            res = addOrd(res, listeTmp->value);
        }
        
        listeTmp = listeTmp->next;        
    }

    while(secondListTmp != NULL) {
        if(findListe(res, secondListTmp->value) == -1) {
            res = addOrd(res, secondListTmp->value);
        }

        secondListTmp = secondListTmp->next;
    }

    return res;
}

/* Exercice 5 : La liste des sommes préfixe */

t_ptr_liste sommeList(t_ptr_liste liste) {
    t_ptr_liste tmp = liste;
    t_ptr_liste prec = NULL;
    
    while(tmp != NULL) {
        if(prec != NULL)
            tmp->value = prec->value + tmp->value;
        
        prec = tmp;
        tmp = tmp->next;
    }
    
    return liste;
} 

/* Libération des ressources */

void freeListe(t_ptr_liste liste) {
    t_ptr_liste next;
    
    while(!est_vide(liste)) {
        next = liste->next;
        free(liste);
        liste = next;
    }
}

int main() {
    /* Création d'une liste */
    
    t_ptr_liste liste = creationListe();
    
    /* Affichage d'une liste */
    
    afficher(liste);

    /* Longeur de la liste */
    
    printf("Longeur de la liste = %d\n", sizeList(liste));
    
    /* Copie de la liste */

    t_ptr_liste newList = copyList(liste);
    printf("New Liste = ");
    afficher(newList);
    
    /* Recherche d'une élément dans une liste */
        
    printf("Pos de 4 = %d\n", findListe(liste, 4));
    
    /* Suppression d'un élément d'un liste */
    
    printf("Suppression de tous les 5 :\n");
    liste = delElem(liste, 5);
    afficher(liste);
    
    /* Insertion dans une liste ordonnée */
    
    t_ptr_liste listeOrd = creationListeOrdonne();
    afficher(listeOrd);
    
    /* Inverse d'une liste */
    
    printf("Inversion de la liste ordonnée :\n");
    listeOrd = inversionListeADT(listeOrd);
    afficher(listeOrd);

    /* Vérification si c'est un palindrome */
    t_ptr_liste palin = NULL;
    palin = ajout_liste(palin, 1);
    palin = ajout_liste(palin, 2);
    palin = ajout_liste(palin, 3);
    palin = ajout_liste(palin, 4);
    palin = ajout_liste(palin, 3);
    palin = ajout_liste(palin, 2);
    palin = ajout_liste(palin, 1);

    printf("Palin :\n");
    afficher(palin);
    printf("La liste palin est un paladrome ? ");
    (isPalindrome(palin) ? printf("Oui\n") : printf("Non\n"));

    t_ptr_liste paPalin = NULL;
    paPalin = ajout_liste(paPalin, 1);
    paPalin = ajout_liste(paPalin, 2);
    paPalin = ajout_liste(paPalin, 3);
    paPalin = ajout_liste(paPalin, 4);
    printf("Pas Palin :\n");
    afficher(paPalin);
    printf("La liste papalin est un paladrome ? ");
    (isPalindrome(paPalin) ? printf("Oui\n") : printf("Non\n"));

    /* Vérification que la liste est une suite de Fibonacci */
    t_ptr_liste fibList = NULL;
    fibList = ajout_liste(fibList, 3);
    fibList = ajout_liste(fibList, 2);
    fibList = ajout_liste(fibList, 1);
    fibList = ajout_liste(fibList, 1);
    fibList = ajout_liste(fibList, 0);
    printf("fibList :\n");
    afficher(fibList);
    printf("La liste fibList est une liste de Fibonacci ? ");
    (isFibonnacciList(fibList) ? printf("Oui\n") : printf("Non\n"));

    /* Fusion de deux liste triée */
    printf("Fusion de listeOrd et de paPalin\n");
    t_ptr_liste testFusion = fusionList(listeOrd, paPalin);
    afficher(testFusion);

    printf("Fusion de listeOrd et de paPalin (sans répétition)\n");
    testFusion = fusionListNoRepeat(listeOrd, paPalin);
    afficher(testFusion);

    /* Liste des sommes préfixe */
    t_ptr_liste listeSomme = NULL;
    listeSomme = ajout_liste(listeSomme, 3);
    listeSomme = ajout_liste(listeSomme, 5);
    listeSomme = ajout_liste(listeSomme, 4);
    listeSomme = ajout_liste(listeSomme, 2);
    listeSomme = ajout_liste(listeSomme, 1);
    listeSomme = sommeList(listeSomme);
    printf("La liste des sommes préfixe donne : \n");
    afficher(listeSomme);

    /* Libération de la mémoire */
    freeListe(listeOrd);
    freeListe(liste);
    freeListe(newList);
    freeListe(palin);
    freeListe(paPalin);
    freeListe(fibList);
    freeListe(testFusion);
    freeListe(listeSomme);

    return 0;
}
 
