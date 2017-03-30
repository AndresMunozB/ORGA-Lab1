addi $t4, $zero, -5
addi $t5, $zero, 15
addi $s0, $zero, 10
add $t5, $t5, $t4

BRANCH:
blt $t5, $zero, MENOR
bgt $t5, $zero, MAYOR
MENOR:
sub $s3, $zero, $t5
addi $t1, $zero, 10
sub $s3, $s3, $t1
j END

MAYOR:
add $t6, $t5, $zero 
mul $t6, $t6, $t6
sub $t5, $t5, $t6
j BRANCH

END:
div $s2, $s3, $s0
div $s6, $s3, $t5