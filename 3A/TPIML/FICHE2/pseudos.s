#-----------------------------------------------------------------
#-- File name : pseudos.s
#-- Objet : TP Interface Matériel Logiciel - Fiche 2
#--
#-- Exercice 1 - Fiche de td 2 (traduction de pseudo-instructions)
#    Les pseudo instructions mises en commentaires (g et aa) ne 
#    sont pas acceptÈes par le simulateur (version 6.5 )
#----------------------------------------------------------------

	.text
label1:
	move $t1, $t3	#a
	li  $5, 0xFFFF	#b
	li  $5, 0x0FFFF	#c
	li  $3, 0xAFF2AD #d
	li  $5, 50000	#e
	li  $5, -50000 #f
	#addiu $5, $3, 0xAFF2AD #g Le simulateur 6.5 ne l'accepte pas
	div $v0, $a1, $a2 #h
	mul $t0, $t1, $t2 #i
    mul $5, $7, 42000 #j
	abs  $5, $4 #k
	sge $16, $17, 0x43661 #l
	lw $7, 0x329FF0($5)#m
	lw  $6, 0xFFFF($5) #n	
	lw  $6, 0x0FFFF($5) #o
	bgt $7, $6, label2  #p) Le simulateur n'accepte pas les déplacements
	                   # en langage d'assemblage (le programmeur ne sait pas
			   # comment les pseudo-instructions seront traduites)
	bge $7, $6, label1 #q) même remarque qu'en p)
	beq $7, $6, label #r	
        ld $16, 1032	 #s
	ld $16, 1032($s1) #t
    rem $t0, $t1, $t2 #u
	rol $s5, $s0, 11 #v
	la $5, 500($7) #w
    la $a1, label #x
	lw   $5, label($7) #y
    lw  $a2, label+80($a1)#z
    # sw  $6, label-20($5) #aa #Mode d'adressage non accepté par xspim 6.5
    li   $5, 0x789AEF1234 #ab
 	li   $5, 6000000000 #ac
 	
label2:
label:
#------------------------------------------------------------
