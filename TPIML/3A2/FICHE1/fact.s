.data
.align 2
RESULTAT: .space 4
DEPASSEMENT: .asciiz "Erreur : Depassement de capacite\n"
.text
.globl main

main:

debut:
    addi $t0, $t0, 1
    sw $t0, RESULTAT($0)
    li $s0, 50
    li $t1, 1
boucle:
    blt $s0, $t1, suite
    lw $t2, RESULTAT($0)
    mul $t2, $t2, $s0
    bltz $t2, erreur 
    sw $t2, RESULTAT($0)
    addi $s0, $s0, -1
    beq $0, $0, boucle
erreur:
    li $v0, 4
    la $a0, DEPASSEMENT
    syscall
suite:
    li $v0, 1
    lw $a0, RESULTAT($0)
    syscall
    jr $ra

