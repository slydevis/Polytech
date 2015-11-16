.text
label1: 
  ld $16, 0($20)
  ld $16, 20($16)
  mulo $t1, $t2, $t3
  mulou $t1, $t2, $t3
  mulo $t1, $t2, 4
  remu $t1, $t2, $t3
  rem $t1, $t2, 0x12345
