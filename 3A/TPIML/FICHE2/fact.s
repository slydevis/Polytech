#-----------------------------------------------------------------
#-- File name : somme.s
#-- Objet : TP Interface MatŽriel Logiciel  - Fiche 2
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


# Algo 
# FACT = 50
# RES = 0
# while(FACT >= 1) {
#   RES = RES * FACT
#   FACT = FACT - 1;
# }

     	.align 2  # non necessaire 
RES : .space 4  # ou .word 0 pour faire RES <--- 0
	.text
	.globl main
main :
# debut :
debut :
    
#   RES <---0
    li $t1, 1
	sw $t1, RES($0)
#   FACT <--- 10
	li $s0, 10
#boucle: Si FACT < 1 aller a suite
	li $t1, 1
boucle:	

	blt $s0, $t1, suite
#        sinon 
#   RES <--- RES * FACT
	lw $t2, RES($0)
	mulo $t2,$t2, $s0
	sw  $t2, RES($0)
#   FACT <--- FACT -1 
	addi $s0, $s0, -1
#          aller a boucle
	beq $0, $0, boucle    # ou j boucle
#        finsi
#suite: afficher(RES)
suite:  
# instructions pour afficher l'entier en mémoire à l'adresse RES($0)
	li $v0, 1    # system call code for print_int (see page A.49)
	lw $a0, RES($0) # integer to print
	syscall      # print
#fin
	jr $ra         # Retour de la procedure main.
#----------------------------------------------------------------------------

