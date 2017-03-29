addi $t0, $zero, 5

while:
bgt $t0, $zero, cuerpoWhile
j segundoWhile
cuerpoWhile:
add $t1, $t1, $t0
mul $t2, $t1, $t0
subi $t0, $t0, 1
j while

segundoWhile:
bgt $t1, $zero, cuerpoSegundoWhile
j fin
cuerpoSegundoWhile:
subi $t0, $t1, 1
mul $t2, $t1, $t0
subi $t1, $t1, 1
j segundoWhile

fin: