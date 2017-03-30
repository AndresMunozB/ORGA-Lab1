addi $t1, $zero, 10
jal FUNCION
addi $t1, $zero, 7
j END
FUNCION:
addi $t1, $zero, 5
jr $ra
END:

