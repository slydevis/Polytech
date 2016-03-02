#------------------------------------------------------------------
# Fichier noyau2-1.s
# Objet : TP Interface Matériel Logiciel - Fiche 4
# Ce fichier est une modification du programme de traitement
# d'exceptions par défaut de spim.
# Ce noyau (traitant des exceptions) traite l'IT clavier en
# affichant le message "IT clavier: " suivi du code du
# caractère tapé
# Pour les autres exceptions on  ne fait qu'afficher
# un message d'erreur et relancer le programme utilisateur.
#--------------------------------------------------------------------
# 1) L'entête original : vous pouvez passer


# SPIM S20 MIPS simulator.
# The default trap handler for spim.
#
# Copyright (C) 1990-2003 James Larus, larus@cs.wisc.edu.
# ALL RIGHTS RESERVED.
#
# SPIM is distributed under the following conditions:
#
# You may make copies of SPIM for your own use and modify those copies.
#
# All copies of SPIM must retain my name and copyright notice.
#
# You may not sell SPIM or distributed SPIM in conjunction with a commerical
# product or service without the expressed written consent of James Larus.
#
# THIS SOFTWARE IS PROVIDED ``AS IS'' AND WITHOUT ANY EXPRESS OR
# IMPLIED WARRANTIES, INCLUDING, WITHOUT LIMITATION, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE.
#

# $Header: $


# 2) Les données du noyau :  

# Define the exception handling code.  This must go first!

	.kdata
# 2.1) Les constantes chaînes de caractères
msgBreak: .asciiz "Break "
msg_brk_invalide: .asciiz "Service systeme non implante\n"
alaligne: .asciiz "\n"
msgIt: .asciiz "IT clavier: "


__m1_:	.asciiz "  Exception "
__m2_:	.asciiz " occurred and ignored\n"
__e0_:	.asciiz "  [Interrupt] "
__e1_:	.asciiz	""
__e2_:	.asciiz	""
__e3_:	.asciiz	""
__e4_:	.asciiz	"  [Unaligned address in inst/data fetch] "
__e5_:	.asciiz	"  [Unaligned address in store] "
__e6_:	.asciiz	"  [Bad address in text read] "
__e7_:	.asciiz	"  [Bad address in data/stack read] "
__e8_:	.asciiz	"  [Error in syscall] "
__e9_:	.asciiz	"  [Breakpoint] "
__e10_:	.asciiz	"  [Reserved instruction] "
__e11_:	.asciiz	""
__e12_:	.asciiz	"  [Arithmetic overflow] "
__e13_:	.asciiz	"  [Inexact floating point result] "
__e14_:	.asciiz	"  [Invalid floating point result] "
__e15_:	.asciiz	"  [Divide by 0] "
__e16_:	.asciiz	"  [Floating point overflow] "
__e17_:	.asciiz	"  [Floating point underflow] "
# On range les adresses des divers message dans un tableau indexé
# pour pouvoir les afficher en utilisant le même "bout de code"
__excp:	.word __e0_,__e1_,__e2_,__e3_,__e4_,__e5_,__e6_,__e7_,__e8_,__e9_
	.word __e10_,__e11_,__e12_,__e13_,__e14_,__e15_,__e16_,__e17_

#les 4 mots ci-dessous sont utilisés pour sauvegarder 5 registres $v0, $a0,
# $t0, et $t1
# le registre $at est sauvegardé dans le registre $k1

save_v0:.word 0
save_v1:.word 0
save_a0:.word 0
save_a1:.word 0
save_a2:.word 0
save_a3:.word 0
save_t0:.word 0
save_t1:.word 0
save_t2:.word 0
save_t3:.word 0
save_t4:.word 0
save_t5:.word 0
save_t6:.word 0
save_t7:.word 0
save_s0:.word 0
save_s1:.word 0
save_s2:.word 0
save_s3:.word 0
save_s4:.word 0
save_s5:.word 0
save_s6:.word 0
save_s7:.word 0
save_t8:.word 0
save_t9:.word 0
save_gp:.word 0
save_sp:.word 0
save_ra:.word 0
save_HI:.word 0
save_LO:.word 0
save_fp:.word 0

elu: .word 0

# Entrée 0
TPC_at:.word 0
TPC_v0:.word 0
TPC_v1:.word 0
TPC_a0:.word 0
TPC_a1:.word 0
TPC_a2:.word 0
TPC_a3:.word 0
TPC_t0:.word 0
TPC_t1:.word 0
TPC_t2:.word 0
TPC_t3:.word 0
TPC_t4:.word 0
TPC_t5:.word 0
TPC_t6:.word 0
TPC_t7:.word 0
TPC_s0:.word 0
TPC_s1:.word 0
TPC_s2:.word 0
TPC_s3:.word 0
TPC_s4:.word 0
TPC_s5:.word 0
TPC_s6:.word 0
TPC_s7:.word 0
TPC_t8:.word 0
TPC_t9:.word 0
TPC_gp:.word 0
TPC_sp:.word 0
TPC_ra:.word 0
TPC_HI:.word 0
TPC_LO:.word 0
TPC_fp:.word 0
TPC_Status: .word 1 # 0 = Inactif/Terminer; 1 = actif ; 2 = Bloque
TPC:.word main0
TPC_Entree: .word main0
# Entrée 1
    .space 136

# save minimal : $t1, $t0, $a0, $ra, $at, PC

# This is the exception handler code that the processor runs when
# an exception occurs. It only prints some information about the
# exception, but scan server as a model of how to write a handler.
#
# Because we are running in the kernel, we can use $k0/$k1 without
# saving their old values.

# 3) Le code du noyau.

	.ktext 0x80000080
	.set noat
	move $k1 $at		# Save $at
	# sw $at, save_at($0)
	.set at
	sw $v0, save_v0($0) # Not re-entrent and we can't trust $sp
	sw $v1, save_v1($0)
	sw $a0, save_a0($0) # But, we need to use these registers
	sw $a1, save_a1($0)
	sw $a2, save_a2($0)
	sw $a3, save_a3($0)
	sw $t0, save_t0($0)
	sw $t1, save_t1($0)
	sw $t2, save_t2($0)
	sw $t3, save_t3($0)
	sw $t4, save_t4($0)
	sw $t5, save_t5($0)
	sw $t6, save_t6($0)
	sw $t7, save_t7($0)
	sw $s0, save_s0($0)
	sw $s1, save_s1($0)
	sw $s2, save_s2($0)
	sw $s3, save_s3($0)
	sw $s4, save_s4($0)
	sw $s5, save_s5($0)
	sw $s6, save_s6($0)
	sw $s7, save_s7($0)
	sw $t8, save_t8($0)
	sw $t9, save_t9($0)
	sw $gp, save_gp($0)
	sw $sp, save_sp($0)
	sw $ra, save_ra($0)
	mfhi $t0 # pour sauvegarder $hi, save_HI($0)
	sw $t0, save_HI($0)
	mflo $t0 # pour sauvegarder $lo, save_LO($0)
	sw $t0, save_LO($0)
	sw $fp, save_fp($0)

	mfc0 $k0 $13		# Cause register
    srl $a0 $k0 2		# Extract ExcCode Field
	andi $a0 $a0 0xf

    # Test si appel système break, et  on laisse tel quel le traitement
    # des autres exceptions.
    bne $a0, 9, autres_exceptions
appel_systeme_break:
    mtc0 $0, $13    # Clear Cause register

    #affiche "Break"
    la  $a0,  msgBreak
    li  $v0, 4
    syscall

	#$t0 <- numero du service
	mfc0 $t0, $14 # EPC : adresse de l'instruction break
	lw $t0, 0($t0) # Code de l'instruction breakA
	srl $t0, $t0, 11
    #Ecrire le numéro du break
    move $a0,$t0
    li  $v0, 1
    syscall
  	la  $a0, alaligne
    li  $v0,  4
    syscall
	
	# afficher le message service non supporté
	la $a0, msg_brk_invalide
	li $v0,4
	syscall
	j ret

#------------------------------------------------------------
autres_exceptions:
    bnez $a0 pas_interruption 
interruption: # Forcément IT clavier
	la $a0, msgIt
	li $v0, 4
	syscall

	# lire le code de la touche et l'afficher
	lw $t0, 0xFFFF0004($0)
	# Si la touche et q ou Q change le processus courant
	beq $t0, 113, changeProcess # touche q
	beq $t0, 81, changeProcess # touche Q

# 0, 1, 2, 3 : on crée (s’il n’existe pas déjà) ou on réveille (s’il existe et est bloqué) respectivement le processus 0, 1, 2, 3
    beq $t0, 48, createProcess # touche 0
    beq $t0, 49, createProcess # touche 1
    beq $t0, 50, createProcess # touche 2
    beq $t0, 51, createProcess # touche 3

# a, b, c, d : on bloque respectivement le processus 0, 1, 2, 3 (ne fait rien si le processus est déjà terminé ou est bloqué)
#    beq $t0, 97, # touche a
#    beq $t0, 98, # touche b
#    beq $t0, 99, # touche c
#    beq $t0, 100, # touche d
    
# A, B, C, D : on termine respectivement le processus 0, 1, 2, 3 (ne fait rien si le processus est déjà terminé).
#    beq $t0, 65, endProcess # touche A
#    beq $t0, 66, endProcess # touche B
#    beq $t0, 67, endProcess # touche C
#    beq $t0, 68, endProcess # touche D
    
	move $a0, $t0
	li $v0, 1
	syscall
    # Passer à la ligne pour plus de "lisibilité"
	la $a0, alaligne
	li $v0, 4
	syscall
	j int_ret
	
createProcess:
    addi $t0, $t0, -48 # On récupère le numéro de processus
    
    # On change l'elu
	li $t1, 5
	rem $t0, $t0, $t1
	sw $t0, elu
	
    li $t1, 136
    mul $t0, $t0, $t1 # on récupère la table des processus correspondant
	lw $t1, TPC_Status($t0)
    li $t2, 1
    sw $t0
    bne $t1, $0, wakeProcess
    # On initialise les registre de ce nouveau processus
    sw $0, TPC($t0)
wakeProcess:
    li $t1, 1
    sw $t1, TPC_Status($t0)
    la $k0, TPC_Entree($t0)
changeProcess:
    # on change elu
    lw $t0, elu
    li $t1, 136
    mul $t0, $t0, $t1

    mfc0 $k0, $14
    addi $k0, $k0, 4
    sw $k0, TPC($t0)

    lw $t1, save_v0($0)
    sw $t1, TPC_v0($t0)
	lw $t1, save_v1($0)
    sw $t1, TPC_v1($t0)
	lw $t1, save_a0($0) # But, we need to use these registers
	sw $t1, TPC_a0($t0)
	lw $t1, save_a1($0)
	sw $t1, TPC_a1($t0)
	lw $t1, save_a2($0)
	sw $t1, TPC_a2($t0)
	lw $t1, save_a3($0)
	sw $t1, TPC_a3($t0)
	lw $t1, save_t0($0)
	sw $t1, TPC_t0($t0)
	lw $t1, save_t1($0)
	sw $t1, TPC_t1($t0)
	lw $t1, save_t2($0)
	sw $t1, TPC_t2($t0)
	lw $t1, save_t3($0)
	sw $t1, TPC_t3($t0)
	lw $t1, save_t4($0)
	sw $t1, TPC_t4($t0)
	lw $t1, save_t5($0)
	sw $t1, TPC_t5($t0)
	lw $t1, save_t6($0)
	sw $t1, TPC_t6($t0)
	lw $t1, save_t7($0)
	sw $t1, TPC_t7($t0)
	lw $t1, save_s0($0)
	sw $t1, TPC_s0($t0)
	lw $t1, save_s1($0)
	sw $t1, TPC_s1($t0)
	lw $t1, save_s2($0)
	sw $t1, TPC_s2($t0)
	lw $t1, save_s3($0)
	sw $t1, TPC_s3($t0)
	lw $t1, save_s4($0)
	sw $t1, TPC_s4($t0)
	lw $t1, save_s5($0)
	sw $t1, TPC_s5($t0)
	lw $t1, save_s6($0)
	sw $t1, TPC_s6($t0)
	lw $t1, save_s7($0)
	sw $t1, TPC_s7($t0)
	lw $t1, save_t8($0)
	sw $t1, TPC_t8($t0)
	lw $t1, save_t9($0)
	sw $t1, TPC_t9($t0)
	lw $t1, save_gp($0)
	sw $t1, TPC_gp($t0)
	lw $t1, save_sp($0)
	sw $t1, TPC_sp($t0)
	lw $t1, save_LO($0)
	sw $t1, TPC_LO($t0)
	lw $t1, save_HI($0)
	sw $t1, TPC_HI($t0)

	lw $k1, TPC_at($t0)
	sw $ra, TPC_ra($t0)
	mflo $k1
	sw $k1, TPC_LO($t0)
	mfhi $k1
	sw $k1, TPC_HI($t0)

	lw $t1, save_fp($0)
	sw $t1, TPC_fp($t0)

	lw $t0, elu
	addi $t0, 1
	li $t1, 2
	rem $t0, $t0, $t1
	sw $t0, elu

	li $t1, 136
	mul $t0, $t0, $t1
	lw $a0, TPC_a0($t0)
	lw $v0, TPC_v0($t0)
	mtlo $k1
	lw $k1, TPC_HI($t0)
	mthi $k1
	lw $k1, TPC_LO($t0)

	lw $ra, TPC_ra($t0)
	lw $k0, TPC($t0)
	lw $t1, TPC_t1($t0)
	lw $t0, TPC_t0($t0)

	.set noat
	move $at, $k1
	.set at
	rfe
	jr $k0

endProcess:
    # code de la touche dans $t0
    
pas_interruption:
	# Print information about exception.
	#
	li $v0 4		# syscall 4 (print_str)
	la $a0 __m1_
	syscall

	li $v0 1		# syscall 1 (print_int)
    srl $a0 $k0 2		# Extract ExcCode Field
	andi $a0 $a0 0xf
	syscall

	li $v0 4		# syscall 4 (print_str)
	lw $a0 __excp($k0)
	syscall

	bne $k0 0x18 ok_pc	# Bad PC exception requires special checks
    nop

	mfc0 $a0, $14		# EPC
	andi $a0, $a0, 0x3	# Is EPC word-aligned?
	beq $a0, 0, ok_pc
    nop

	li $v0 10		# Exit on really bad PC
	syscall

ok_pc:
	li $v0 4		# syscall 4 (print_str)
	la $a0 __m2_
	syscall

	mtc0 $0, $13		# Clear Cause register

# Return from exception. Skip offending
# instruction to avoid infinite loop.
#
ret:
	lw $v0 save_v0($0)	# Restore regs
	lw $a0 save_a0($0)
	lw $t0 save_t0($0)
	lw $t1, save_LO($0)
	mtlo $t1
	lw $t1, save_HI($0)
	mthi $t1
	lw $t1 ,save_t1($0)

	mfc0 $k0 $14		# EPC
	addiu $k0 $k0 4		# Return to next instruction
	.set noat
	move $at $k1		# Restore $at
	.set at
	rfe			# Return from exception handler
	jr $k0

# Return from interrupt. Don't skip instruction
# since it has not executed.
#
int_ret:
	lw $v0, save_v0($0)		# Restore regs
	lw $a0, save_a0($0) 
	lw $t0, save_t0($0)
	mtlo $t1
	lw $t1, save_HI($0)
	mthi $t1
	lw $t1, save_t1($0)
	lw $t1, save_LO($0)
	
	mfc0 $k0 $14		# EPC (return to EPC)
	.set noat
	move $at $k1		# Restore $at
	.set at
	rfe			# Return from exception handler
	jr $k0


#-----------------------------------------------------------------
# Point d'entrée 
#----------------------------------------------------------------

	.globl __start
__start:

# Configurer le receiver en mode interruptions (mettre 2 dans
# le bit interrupt enable du registre de controle du receiver
# -adresse 0xffff0000)
	li $t0, 2
	sw $t0, 0xffff0000($0) # receiver en mode interrupt
# Lancer le programme de test à l'étiquette main 
# Le programme de test fonctionne en mode utilisateur
	# On modifie le registre status en lui affectant la valeur
        # 0x0000010C. On reste donc en mode maître interruptions
        # masquées (les 2 bits de poids faibles sont à 0)
	li $k0, 0x10C
	mtc0 $k0, $12

	# On met dans $k0 l'adresse du début du programme
	la $k0, main0
	sw $k0, TPC_Entree($0)
	sw $k0, TPC($0)
	
	# on met le numéro du programme qui commence dans la variable elu
	sw $0, elu
	# On initialise l'adresse des différents programme dans le registre $k1
	la $k1, main1
	sw $k1, TPC+136($0) # k0 -> première entrée de TPC
	sw $0, TPC_Status+136($0)
	sw $k1, TPC_Entree+136($0)
	
	la $k1, main2
	sw $k1, TPC+272($0)
	sw $k1, TPC_Entree+272($0)
	sw $0, TPC_Status+272($0)
	
	la $k1, main3
	sw $k1, TPC+408($0)
	sw $k1, TPC_Entree+408($0)
	sw $0, TPC_Status($0)
	
	la $k1, main4
	sw $k1, TPC+544($0)
	sw $k1, TPC_Entree+544($0)
	
	# Commutation de contextes (changer status et PC de façon atomique
        # avec les 2 instructions suivantes)
	rfe # Au prochain jr, status aura la valeur 0x103, et on sera donc
            # en mode utilisateur/interruptions démasquées (masque général
            # et masque IT receiver)
	jr $k0

# Terminer l'exécution du programme : service système exit
	li $v0 10
	syscall			# syscall 10 (exit)

# ---------------------------------------------------------------

