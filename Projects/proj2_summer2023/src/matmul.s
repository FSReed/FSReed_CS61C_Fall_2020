.globl matmul

.text
# =======================================================
# FUNCTION: Matrix Multiplication of 2 integer matrices
#   d = matmul(m0, m1)
# Arguments:
#   a0 (int*)  is the pointer to the start of m0
#   a1 (int)   is the # of rows (height) of m0
#   a2 (int)   is the # of columns (width) of m0
#   a3 (int*)  is the pointer to the start of m1
#   a4 (int)   is the # of rows (height) of m1
#   a5 (int)   is the # of columns (width) of m1
#   a6 (int*)  is the pointer to the the start of d
# Returns:
#   None (void), sets d = matmul(m0, m1)
# Exceptions:
#   Make sure to check in top to bottom order!
#   - If the dimensions of m0 do not make sense,
#     this function terminates the program with exit code 38
#   - If the dimensions of m1 do not make sense,
#     this function terminates the program with exit code 38
#   - If the dimensions of m0 and m1 don't match,
#     this function terminates the program with exit code 38
# =======================================================
matmul:

    # Error checks
    li t0, 1
    blt a1, t0, invalid_length
    blt a2, t0, invalid_length
    blt a4, t0, invalid_length
    blt a5, t0, invalid_length

    bne a2, a4, invalid_length
    # Prologue
    addi sp, sp, -40
    sw s0, 0(sp)
    sw s1, 4(sp)
    sw s2, 8(sp)
    sw s3, 12(sp)
    sw s4, 16(sp)
    sw s5, 20(sp)
    sw s6, 24(sp)
    sw s7, 28(sp)
    sw s8, 32(sp)       # s7 and s8 used to store i and j, to avoid frequently store them in the stack during looping.

    sw ra, 36(sp)
    
    mv s0, a0
    mv s1, a1
    mv s2, a2
    mv s3, a3
    mv s4, a4
    mv s5, a5
    mv s6, a6
    
    li s7, 0
outer_loop_start:
    mul t0, s7, s2      # How many units to move from the header of m0
    slli t0, t0, 2      # The true offset
    add t0, t0, s0      # Target row vector

    li s8, 0            # Initialize the column vector in m1
inner_loop_start:
    beq s8, s5, inner_loop_end
    slli t1, s8, 2      # True offset of the column vector
    add t1, t1, s3      # Target col vector
    
    # Get ready to call function dot:
    mv a0, t0
    mv a1, t1
    mv a2, s2
    li a3, 1
    mv a4, s5

    jal dot

    mv t0, a0
    sw t0, 0(s6)
    addi s6, s6, 4
    addi s8, s8, 1
    j inner_loop_start
inner_loop_end:
    addi s7, s7, 1
    bne s7, s1, outer_loop_start
outer_loop_end:


    # Epilogue
    lw s0, 0(sp)
    lw s1, 4(sp)
    lw s2, 8(sp)
    lw s3, 12(sp)
    lw s4, 16(sp)
    lw s5, 20(sp)
    lw s6, 24(sp)
    lw s7, 28(sp)
    lw s8, 32(sp)

    lw ra, 36(sp)
    addi sp, sp, 40     # Forget to place sp back in version 0.1
    jr ra

invalid_length:
    li a0, 38
    j exit