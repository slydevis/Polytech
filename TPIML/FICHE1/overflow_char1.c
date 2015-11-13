/*
-----------------------------------------------------------------
-- File name : overflow_char1.c  
-- Objet : TP Interface Matériel Logiciel 2015/2016 - Fiche 1
-- 
----------------------------------------------------------------
*/
#include <stdio.h>
#include <limits.h>

int main(void)
{
  char cmin=CHAR_MIN ;
  char cmax=CHAR_MAX ;
  char cminMoinsUn = cmin-1;
  char cmaxPlusUn = cmax+1 ;
  
  printf("Overflow : type char \n");
  printf("Plus petit char = %d\n",cmin);
  printf("Plus petit char - 1 = %d\n", cminMoinsUn);
  printf("Plus grand char = %d\n",cmax);
  printf("Plus grand char + 1  = %d\n", cmaxPlusUn);
  return(0);
}

