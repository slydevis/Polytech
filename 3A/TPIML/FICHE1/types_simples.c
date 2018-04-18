/*
-----------------------------------------------------------------
-- File name : types_simples.c
-- Objet : TP Interface Matériel Logiciel 2015/2016 - Fiche 1
-- 
----------------------------------------------------------------
*/
#include <stdio.h>

int main(void)
{
     printf("Types simples\n");
     printf("Taille d'un char : %zu\n", sizeof(char));
     printf("Taille d'un int : %zu\n", sizeof(int));
     printf("Taille d'un short : %zu\n", sizeof(short));
     printf("Taille d'un long : %zu\n", sizeof(long));
     printf("Taille d'un float : %zu\n", sizeof(float));
     printf("Taille d'un double : %zu\n", sizeof(double));
     printf("Taille d'un pointeur sur char : %zu\n",sizeof(char *));
     printf("Taille d'un pointeur sur int : %zu\n",sizeof(int *));
     printf("Taille d'un pointeur sur double : %zu\n",sizeof(double *));
     printf("Taille d'un pointeur de type void * : %zu\n",sizeof(void *));
     return(0);
}
