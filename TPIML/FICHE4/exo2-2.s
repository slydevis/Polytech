#------------------------------------------------------------------
# Fichier exo2-1.s
# Objet : TP Interface Matériel Logiciel - Fiche 4
#         Exercice 2-(i)
# Le programme de ce fichier ne fonctionne que lorsque un noyau
# (traitant des exceptions) du fichier noyau2-1.s est chargé
#-----------------------------------------------------------------
# programme de test : Ce programme boucle indéfiniment
#------------------------------------------------------------

	.text # Le programme de test fonctionne en mode utilisateur
	.globl main0
main0:

    #$t0 contiendra le compteur
	move $t0, $0	
	
boucle_main0:
	la $a0, process0
	li $v0, 4
	syscall
	move $a0,$t0 
	li $v0, 1
	syscall
	la $a0, alaligne
	li $v0, 4
	syscall
	addi $t0,$t0, 1
	jal tempo
	j boucle_main0 # le programme boucle indéfinimemnt

	.globl main1
main1:
    #$t0 contiendra le compteur
	move $t0, $0	
	
boucle_main1:
	la $a0, process1
	li $v0, 4
	syscall
	move $a0,$t0 
	li $v0, 1
	syscall
	la $a0, alaligne
	li $v0, 4
	syscall
	addi $t0,$t0, 1
	jal tempo
	j boucle_main1 # le programme boucle indéfinimemnt
    
    .globl main2
main2:
    #$t0 contiendra le compteur
	move $t0, $0	
	
boucle_main2:
	la $a0, process2
	li $v0, 4
	syscall
	move $a0,$t0 
	li $v0, 1
	syscall
	la $a0, alaligne
	li $v0, 4
	syscall
	addi $t0,$t0, 1
	jal tempo
	j boucle_main2 # le programme boucle indéfinimemnt

    .globl main3
main3:
	move $t0, $0	
boucle_main3:
	la $a0, process3
	li $v0, 4
	syscall
	move $a0,$t0 
	li $v0, 1
	syscall
	la $a0, alaligne
	li $v0, 4
	syscall
	addi $t0,$t0, 1
	jal tempo
	j boucle_main3 # le programme boucle indéfinimemnt

    .globl main4
main4:
	move $t0, $0	
boucle_main4:
	la $a0, process4
	li $v0, 4
	syscall
	move $a0,$t0 
	li $v0, 1
	syscall
	la $a0, alaligne
	li $v0, 4
	syscall
	addi $t0,$t0, 1
	jal tempo
	j boucle_main4 # le programme boucle indéfinimemnt

# ------------------------------------------------------------------
# Procedure tempo : temporisation de quelques secondes
#-------------------------------------------------------------------	
tempo:
	li $t1, 0x300000
boucle_tempo:
	beq $t1, $0, fin_tempo
	addi $t1, $t1, -1
	b boucle_tempo
fin_tempo:
	jr $ra

#-----------------------------------------------------------------
.data  # Section des données utilisateur
	alaligne: .asciiz "\n"
	process0: .asciiz "Processus 0 :"
    process1: .asciiz "Processus 1 :"
    process2: .asciiz "Processus 2 :"
    process3: .asciiz "Processus 3 :"
    process4: .asciiz "Processus 4 : Tache de fond : "
#-------------------------------------------------------------

