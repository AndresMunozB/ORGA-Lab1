addi $a0, $zero, 4
la $s5, ($zero)
jal FUNCION_RECURSIVA
add $s7, $v0, $zero
j END

FUNCION_RECURSIVA:
la $t0, ($a0)
addi $sp, $sp, -8
sw $ra, 0($sp)
sw $s5, 4($sp)
beq $t0, $zero, END_FUNCION
lw $t1, 0($s0)
lw $t2, 4($s0)
add $t4, $t1, $t2
lw $t3, 8($s0)
add $s5, $t4, $t3
addi $s0, $s0, 12
addi $a0, $t0, -1
jal FUNCION_RECURSIVA
END_FUNCION:
lw $ra, 0($sp)
lw $t9, 4($sp)
addi $sp, $sp, 8
add $v0, $v0, $t9
jr $ra

END: