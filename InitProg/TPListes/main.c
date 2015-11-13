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
        pos = 0;
        
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
    /*Création d'une liste */
    
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
    
    /* Libération de la mémoire */
    
    freeListe(listeOrd);
    freeListe(liste);
    freeListe(newList);

    return 0;
}
 
