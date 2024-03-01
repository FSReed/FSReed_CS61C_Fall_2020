addi t0, t0, 4
addi s0, s0, 3
loop:
    addi t0, t0, 2
    addi s0, s0, -1
    bge s0, x0, loop

