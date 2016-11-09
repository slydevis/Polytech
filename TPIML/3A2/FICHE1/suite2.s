.data
.align 2

SOMME : .space 4
LISTE : .align 2
        .space 60
MOY : .space 4
NB : .space 4

newline : 
    .asciiz "\n" 
nameListInverse :
    .asciiz "Liste inversee = "
moyennePrompt :
    .asciiz "Moyenne de la liste = "
sommePrompt :
    .asciiz "Somme = "
nbPrompt:
    .asciiz "NB = "
spacePrompt:
    .asciiz " "
    
.text
.globl main

main:

debut :
	sw $0, SOMME($0)
    li $t0, 0
    li $t2, 0
boucle:	
    # Demande un nombre
    li $v0, 5
    syscall
    # si négatif => goto suite
    blt $v0, 0, suite
    
    sw $v0, LISTE($t0)
    addi $t0, $t0, 4
        
    lw $t2, SOMME($0)
    add $t2, $t2, $v0
    sw $t2, SOMME($0)
    
    bgt $t0, 56, suite # 15*4
	beq $0, $0, boucle
suite:
    # calcul du nombre d'element grace a $t0
    div $t0, $t0, 4 # pas sur de l instructions
    sw $t0, NB($0)
    
    li $v0, 4
    la $a0, nbPrompt
    syscall
    
    li $v0, 1
    lw $a0, NB($0)
    syscall
    
    li $v0, 4
    la $a0, newline
    syscall
    
    # affichage de la somme
    
    li $v0, 4
    la $a0, sommePrompt
    syscall
    
    li $v0, 1
    lw $a0, SOMME($0)
    syscall
    
    li $v0, 4
    la $a0, newline
    syscall
    
    # calcul moyenne
    
    lw $t0, SOMME($0)
    lw $t1, NB($0)
    
    div $t0, $t0, $t1
    
    sw $t0, MOY($0)
    
    # Affichage de la moyenne

    li $v0, 4
    la $a0, moyennePrompt
    syscall
    
    li $v0, 1
    lw $a0, MOY($0)
    syscall
    
    li $v0, 4
    la $a0, newline
    syscall
        
    # affichage inverse
    
    li $v0, 4
    la $a0, nameListInverse
    syscall
    
    lw $t0, NB($0)
    mul $t0, $t0, 4
    addi $t0, $t0, -4
boucle2:
    bltz $t0, fin
    
    li $v0, 1
    lw $a0, LISTE($t0)
    syscall
    
    addi $t0, $t0, -4
    
    li $v0, 4
    la $a0, spacePrompt
    syscall
    
    beq $0, $0, boucle2
fin:
    li $v0, 4
    la $a0, newline
    syscall
    jr $ra
