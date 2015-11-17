#-----------------------------------------------------------------
#-- File name : somme.s
#-- Objet : TP Interface Matriel Logiciel  - Fiche 2
#--
#--     (Voir Cours, chapitre 2 - Langage d'Assemblage
#--                 transparents SPIM : exemple        )
#--  Algorithme SIGMA
# /* Somme des 50 premiers entiers non nuls */
#----------------------------------------------------------------
	.data
# variables :
#    SOMME, COMPTEUR : entiers 
#    SOMME est en memoire et COMPTEUR dans $s0
        .space 48703 
     	.align 2  # non necessaire 
SOMME : .space 4  # ou .word 0 pour faire SOMME <--- 0

	.text
	.globl main
main :
# debut :
debut :

# 	  SOMME <---0
	sw $0, SOMME($0)

#boucle: Si COMPTEUR < 0 aller a suite
	li $v0, 0
boucle:	

	blt $v0, 0, suite
#        sinon 
# SAISIR UN NOMBRE
    li $v0, 5
    syscall
    add $t2, $t2, $v0
    sw $t2, SOMME($0)
#   aller a boucle
	beq $0, $0, boucle    # ou j boucle
#        finsi
# suite: afficher(SOMME)
suite:  
# instructions pour afficher l'entier en mémoire à l'adresse SOMME($0)
	li $v0, 1    # system call code for print_int (see page A.49)
	lw $a0, SOMME($0) # integer to print
	syscall      # print
#fin
	jr $ra         # Retour de la procedure main.
#----------------------------------------------------------------------------

