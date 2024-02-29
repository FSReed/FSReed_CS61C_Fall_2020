addi x0, x0, 3
addi s0, x0, 4
addi t0, x0, 5
mul s0, s0, t0 # s0 = 20

sub s0, t0, s0 # s0 = -15
mul t0, s0, t0 # t0 = -300
srai t0, t0, 1 # t0 = -150
slti t0, t0, -149 # t0 = 1

addi s0, s0, 13
addi t0, t0, 5
xor s1, s0, t0 # s1 = 0b1000 = 8

