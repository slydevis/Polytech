#-----------------------------------------------------------------
#-- File name : liste4.s
#-- Objet : TP Interface Matériel Logiciel  - Fiche 2
#--
#--     (Voir Cours, chapitre 2 - Langage d'Assemblage
#--                 transparents SPIM : exemple        )
#----------------------------------------------------------------
	.data
# variables :
LISTE : .align 2
        .space 80 # Liste[20]
newline : 
    .asciiz "\n"  
	.text
	.globl main
main :
# debut :
debut :
    li $t0, 0 # TAILLE -> 0
	li $v0, 0
boucle:	
#boucle: Si $v0 < 0 aller a suite
	blt $v0, 0, suite
# sinon 
# SAISIR UN NOMBRE
    li $v0, 5
    syscall
    blt $v0, 0, suite
    sw $v0, LISTE($t0)
    addi $t0, $t0, 4
#   aller a boucle
	beq $0, $0, boucle    # goto boucle
suite:  
    addi $s1, $t0, 0 # On stocke la taille du tableau

# En C :
#    int i;
#    int j;
#    int k;
#    i = 0
#    while(i < TAILLE) {
#        j = i;
#        while(j < TAILLE) {
#            k = i;
#            while(k <= j) {
#                printf("%d ", Tab[k]);
#                k = k + 1;
#            }
#            printf("\n");
#            j = j + 1;
#        }
#        i = i + 1;
#    }

# i = $t1
# j = $t2
# k = $t3
addi $t1, $t1, 0 # i = 0
sousSuiteBoucle1:
    bgt $t1, $s1, finSousSuite # if(i >= TAILLE) goto finSousSuite;
    beq $t1, $s1, finSousSuite
    addi $t2, $t1, 0 # j = i
    sousSuiteBoucle2:
        bgt $t2, $s1, finSousSuiteBoucle2 # if(j >= TAILLE) goto finSousSuiteBoucle2;
        beq $t2, $s1, finSousSuiteBoucle2
        addi $t3, $t1, 0 # k = i
        sousSuiteBoucle3:
            bgt $t3, $t2, finSousSuiteBoucle3 # if(k > j) goto finSousSuiteBoucle3;
            li $v0, 1 # printf(TAB[k])
            lw $t4, LISTE($t3)
            addi $a0, $t4, 0
            syscall
            addi $t3, $t3, 4 # ++k
            beq $0, $0, sousSuiteBoucle3
        finSousSuiteBoucle3:    
            li $v0, 4 # printf("\n")
            la $a0, newline
            syscall
            addi $t2, $t2, 4 #  ++j
            beq $0, $0, sousSuiteBoucle2
        finSousSuiteBoucle2:
        addi $t1, $t1, 4 # ++i
        beq $0, $0, sousSuiteBoucle1
finSousSuite:

#fin
	jr $ra         # Retour de la procedure main.
#----------------------------------------------------------------------------

