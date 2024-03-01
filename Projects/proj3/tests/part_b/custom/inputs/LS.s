addi t0, t0, 4
addi s0, s0, 1024
sw t0, 0(s0)
lw a0, 0(s0)

# s0 = 1024
addi t0, t0, -1903 # 0b1000 1001 0001
sb t0, 4(s0)
lh a0, 4(s0)

