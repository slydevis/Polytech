/*
-----------------------------------------------------------------
-- File name : overflow_short2.c
-- Objet : TP Interface Matériel Logiciel 2015/2016 - Fiche 1
-- 
----------------------------------------------------------------
*/
#include <stdio.h>
#include <limits.h>

int main(void)
{
  short smin=SHRT_MIN ;
  short smax=SHRT_MAX ;

  printf("Overflow : type short\n");
  printf("Plus petit short = %d\n",smin);
  printf("Plus petit short - 1 = %d\n", smin-1);
  printf("Plus grand short = %d\n",smax);
  printf("Plus grand short + 1  = %d\n", smax+1);
  return(0);
}

