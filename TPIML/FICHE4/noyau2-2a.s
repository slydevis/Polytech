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
save_a0:.word 0
save_t0:.word 0
save_t1:.word 0
save_hi:.word 0
save_lo:.word 0
# Pour sauvegarder le contexte des programmes.
ELU: .word 0
# Entree 0
TCPat: .word 0
TCPv0: .word 0
TCPv1: .word 0
TCPa0: .word 0
TCPa1: .word 0
TCPa2: .word 0
TCPa3: .word 0
TCPt0: .word 0
TCPt1: .word 0
TCPt2: .word 0
TCPt3: .word 0
TCPt4: .word 0
TCPt5: .word 0
TCPt6: .word 0
TCPt7: .word 0
TCPt8: .word 0
TCPt9: .word 0
TCPs0: .word 0
TCPs1: .word 0
TCPs2: .word 0
TCPs3: .word 0
TCPs4: .word 0
TCPs5: .word 0
TCPs6: .word 0
TCPs7: .word 0
TCPgp: .word 0
TCPsp: .word 0
TCPfp: .word 0
TCPra: .word 0
TCPlo: .word 0
TCPhi: .word 0
TCPPC: .word main0
# Entree 1
	.space 128

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
	.set at
	sw $v0, save_v0($0)	# Not re-entrent and we can't trust $sp
	sw $a0, save_a0($0)	# But, we need to use these registers
	sw $t0, save_t0($0)
	sw $t1, save_t1($0)
	mflo $t0
	sw $t0, save_lo($0)
	mfhi $t0
	sw $t0, save_hi($0)

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
	# lire le code de la touche
	lw $t0, 0xFFFF0004($0)
	# si c'est 'q' (113) ou 'Q' (81), on change de programme
		# test
	li $t1, 113
	beq $t0, $t1, change
	li $t1, 81
	bne $t0, $t1, still
		# Changment de programme
			# Sauvegarde du contexte du programme
				# On met dans t0 le num du programme en cours
				# pour avoir la bonne case du tableau.
change :
	lw $t0, ELU
	li $t1, 128
	mul $t0, $t0, $t1
				# On sauvegarde le compteur ordinal
	mfc0 $k0, $14
	addi $k0, $k0, 4
	sw $k0, TCPPC($t0)
				# Les registres deja sauvegarde :
	lw $t1, save_v0($0)
	sw $t1, TCPv0($t0) 
	lw $t1, save_a0($0)
	sw $t1, TCPa0($t0) 
	lw $t1, save_t0($0)
	sw $t1, TCPt0($t0)
	lw $t1, save_t1($0)
	sw $t1, TCPt1($t0)
	lw $t1, save_lo($0)
	sw $t1, TCPlo($t0)
	lw $t1, save_hi($0)
	sw $t1, TCPhi($t0)
				# le reste...
	sw $k1, TCPat($t0)
	sw $ra, TCPra($t0)
	mflo $k1
	sw $k1, TCPlo($t0)
	mfhi $k1
	sw $k1, TCPhi($t0)
				# On s'arrete ici mais en principe, on devrait tout sauvegarder
			# Mis à jour de ELU
	lw $t0, ELU
	addi $t0, 1
	li $t1, 2
	rem $t0, $t0, $t1
	sw $t0, ELU
			# Restauration des registres du programme qui va être execute
	li $t1, 128
	mul $t0, $t0, $t1
	lw $a0, TCPa0($t0)
	lw $v0, TCPv0($t0)
	lw $k1, TCPlo($t0)
	mtlo $k1
	lw $k1, TCPhi($t0)
	mthi $k1
	lw $k1, TCPat($t0)

	lw $ra, TCPra($t0)
	lw $k0, TCPPC($t0)
	lw $t1, TCPt1($t0)
	lw $t0, TCPt0($t0)
	.set noat
	move $at, $k1		# Restore $at
	.set at
	rfe			# Return from exception handler
	jr $k0



still:
	#sinon, on affiche la touche
	move $a0, $t0
	li $v0, 1
	syscall
        # Passer à la ligne pour plus de "lisibilité"
	la $a0, alaligne
	li $v0, 4
	syscall
	j int_ret

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
ret:	lw $v0 save_v0($0)	# Restore regs
	lw $a0 save_a0($0)
	lw $t0 save_t0($0)
	lw $t1, save_lo($0)
	mtlo $t1
	lw $t1, save_hi($0)
	mthi $t1
	lw $t1 save_t1($0)

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
int_ret:lw $v0, save_v0($0)		# Restore regs
	lw $a0, save_a0($0) 
	lw $t0, save_t0($0)
	mtlo $t1
	lw $t1, save_hi($0)
	mthi $t1
	lw $t1, save_t1($0)
	lw $t1, save_lo($0)

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
	# mettre l'adresse du point d'entrée du programme de test dans $k0
	la $k0, main0
	# on met le numero du programme qui commence :
	sw $0, ELU
	# Initialisation entree processus 1
	la $k1, main1
	sw $k1, TCPPC+128($0)
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

