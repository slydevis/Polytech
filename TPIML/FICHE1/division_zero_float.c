/*
-----------------------------------------------------------------
-- File name : division_zero_float.c
-- Objet : TP Interface Matériel Logiciel 2015/2016 - Fiche 1
-- 
----------------------------------------------------------------
*/
#include <stdio.h>
#include <limits.h>

int main(void)
{
  float x ;
  float y = 0.0;

  printf ("Test division d'un float par zero\n");
  printf ("Entrez un float : ");
  scanf("%f",&x);
  printf("%f / 0 = %f\n", x, x/y);
  printf ("Fin du programme division_zero_float\n");
  return(0);
}

