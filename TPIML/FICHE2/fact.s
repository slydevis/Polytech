#-----------------------------------------------------------------
#-- File name : somme.s
#-- Objet : TP Interface Matériel Logiciel  - Fiche 2
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
     	.align 2  # non necessaire 
SOMME : .space 4  # ou .word 0 pour faire SOMME <--- 0
FACT : .space 4
	.text
	.globl main
main :
# debut :
debut :

# 	SOMME <---0
	sw $0, SOMME($0)
#	COMPTEUR <--- 50
	li $s0,5 # !5 = 120
#boucle: Si COMPTEUR < 1 aller a suite
	li $t1, 1
#	FACT <---- 1
	li $t2, 1
	sw $t2, FACT($0)
boucle:	
	blt $s0, $t1, suite
#        sinon 
#          SOMME <--- SOMME + COMPTEUR
	lw $t2, SOMME($0)
	lw $t3, FACT($0)
	mulo $t2,$t3, $s0
	sw  $t2, SOMME($0)
	sw $t3, FACT($0)
#          COMPTEUR <--- COMPTEUR -1 
	addi $s0, $s0, -1
#          aller a boucle
	beq $0, $0, boucle    # ou j boucle
#        finsi
#suite: afficher(SOMME)
suite:  
# instructions pour afficher l'entier en mÈmoire ‡ l'adresse SOMME($0)
	li $v0, 1    # system call code for print_int (see page A.49)
	lw $a0, SOMME($0) # integer to print
	syscall      # print
#fin
	jr $ra         # Retour de la procedure main.
#----------------------------------------------------------------------------

