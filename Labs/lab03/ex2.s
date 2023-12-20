.globl main

.data
source:
    .word   3
    .word   1
    .word   4
    .word   1
    .word   5
    .word   9
    .word   0
dest:
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0
    .word   0

.text
fun:
    addi t0, a0, 1      # Use a0 as argument x, t0 stores (x + 1), t1, stores x
    sub t1, x0, a0      # t1 = -x
    mul a0, t0, t1      # Use a0 for returning from fun!
    jr ra

main:
    # BEGIN PROLOGUE
    addi sp, sp, -20    # This gives a 5-word space in stack
    sw s0, 0(sp)        # Saves s0 to s3 and ra. I think this is considering this file as a callee
    sw s1, 4(sp)
    sw s2, 8(sp)
    sw s3, 12(sp)
    sw ra, 16(sp)
    # END PROLOGUE
    addi t0, zero, 0
    addi s0, zero, 0    # t0 = s0 = 0, s0 is the sum result of the program, and t0 stands for k. Explain later
    la s1, source       # Pointer to source is s1
    la s2, dest         # Pointer to dest is s2
loop:
    slli s3, t0, 2      # ? -> Times the index by 4, store it into s3. t0 goes through 0, 1, 2, 3,..., so t0 stands for k. And s3 stands for the actual address
    add t1, s1, s3      # t1 stores the actual address of the current integer in source. Once used, we don't care about t1 anymore
    lw t2, 0(t1)        # t2 stores this integer
    beq t2, x0, exit    # -------- Exit Here: If source[t0] == 0, exit
    add a0, x0, t2      # Give this integer to fun, as argument in a0
    addi sp, sp, -8     # Use another 2-word space in stack, for temporary registers
    sw t0, 0(sp)
    sw t2, 4(sp)
    jal fun
    lw t0, 0(sp)
    lw t2, 4(sp)        # Only care about t0 and t2, don't care which registers fun uses(t0 and t1), and t1 is already a garbage now.
    addi sp, sp, 8      # restore sp
    add t2, x0, a0      # t2 = result of fun.
    add t3, s2, s3      # t3 now stands for the corresponding actual address of dest.
    sw t2, 0(t3)        # save this result into the corresponding position of dest.
    add s0, s0, t2      # s0 += t2, so s0 stands for the final sum result.
    addi t0, t0, 1      # Add t0 with 1. This is why t0 represents k
    jal x0, loop        # Back to the beginning of the loop
exit:
    add a0, x0, s0
    # BEGIN EPILOGUE
    lw s0, 0(sp)
    lw s1, 4(sp)
    lw s2, 8(sp)
    lw s3, 12(sp)
    lw ra, 16(sp)
    addi sp, sp, 20
    # END EPILOGUE
    addi, a1, a0, 0
    # addi, a0, zero, 1
    # ecall # This will give the return value: -156!
    # addi a0, zero, 10
    # ecall
    jr ra