     	.align 2
SOMME : .space 4

	.text
	.globl main
main :
debut :
	sw $0, SOMME($0)
	li $v0, 0
boucle:	
    li $v0, 5
    syscall
    blt $v0, 0, suite
    
    add $t2, $t2, $v0
    sw $t2, SOMME($0)
	beq $0, $0, boucle
suite:  
	li $v0, 1
	lw $a0, SOMME($0)
	syscall
	jr $ra
