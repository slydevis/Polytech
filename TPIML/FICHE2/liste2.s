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
     	.align 2  # non necessaire
SOMME : .space 4  # ou .word 0 pour faire SOMME <--- 0
LISTE : .align 2
        .space 80 # Liste[20]
MOY : .space 4

newline : 
    .asciiz "\n" 
nameList :
    .asciiz "Liste = "
nameListInverse :
    .asciiz "Liste inversee = "
moyennePrompt :
    .asciiz "Moyenne de la liste = "
nombreElemPrompt :
    .asciiz "Nombre d'elements = "
sommePrompt :
    .asciiz "Somme = "
    
	.text
	.globl main
main :
# debut :
debut :

# 	  SOMME <---0
	sw $0, SOMME($0)
    li $t0, 0
#boucle: Si COMPTEUR < 0 aller a suite
	li $v0, 0
boucle:	

	blt $v0, 0, suite
#        sinon 
# SAISIR UN NOMBRE
    li $v0, 5
    syscall
    blt $v0, 0, suite
    sw $v0, LISTE($t0)
    addi $t0, $t0, 4
    add $t2, $t2, $v0
    sw $t2, SOMME($0)
#   aller a boucle
	beq $0, $0, boucle    # ou j boucle
#        finsi
# suite: afficher(SOMME)
suite:  
    add $s1, $s1, $t0
    addi $s1, $s1, -4
    li $v0, 4
    la $a0, nombreElemPrompt
    syscall
    li $v0, 1
    addi $a0, $s1, 0
    addi $a0, $a0, 4
    div $a0, $a0, 4
    syscall
    li $v0, 4
    la $a0, newline
    syscall
    
    addi $s1, $s1, 4
# affichage de la liste
    li $t0, 0
    li $v0, 4
    la $a0, nameList
    syscall
affichageListe :
    bgtu $t0, $s1, suiteAffichageListe
	li $v0, 1    # system call code for print_int (see page A.49)
	lw $a0, LISTE($t0) # integer to print
	syscall      # print
	addi $t0, $t0, 4
	beq $0, $0, affichageListe
suiteAffichageListe :
    li $v0, 4
    la $a0, newline
    syscall
    li $v0, 4
    la $a0, nameListInverse
    syscall
affichageInverse :
   blt $t0, 4, suiteAffichageListeInverse 
   addi $t0, $t0, -4
   li $v0, 1
   lw $a0, LISTE($t0)
   syscall
   beq $0, $0, affichageInverse
suiteAffichageListeInverse :
    li $v0, 4
    la $a0, newline
    syscall
sommeAffichage:
    li $v0, 4
    la $a0, sommePrompt
    syscall
    li $v0, 1
    lw $a0, SOMME($0)
    syscall
    li $v0, 4
    la $a0, newline
    syscall
    li $v0, 4
    la $a0, moyennePrompt
    syscall
calculMoyenne :
    lw $t3, SOMME($0)
    addi $t2, $s1, 0
    div $t2, $t2, 4
   
    div $t2, $t3, $t2
    sw $t2, MOY($0)
suiteMoyenne :
    li $v0, 1
    lw $a0, MOY($0)
    syscall    
# instructions pour afficher l'entier en mémoire à l'adresse SOMME($0)
#	li $v0, 1    # system call code for print_int (see page A.49)
#	lw $a0, SOMME($0) # integer to print
#	syscall      # print
#fin
	jr $ra         # Retour de la procedure main.
#----------------------------------------------------------------------------

