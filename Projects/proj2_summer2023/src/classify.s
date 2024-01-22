.globl classify

.text
# =====================================
# COMMAND LINE ARGUMENTS
# =====================================
# Args:
#   a0 (int)        argc
#   a1 (char**)     argv
#   a1[1] (char*)   pointer to the filepath string of m0
#   a1[2] (char*)   pointer to the filepath string of m1
#   a1[3] (char*)   pointer to the filepath string of input matrix
#   a1[4] (char*)   pointer to the filepath string of output file
#   a2 (int)        silent mode, if this is 1, you should not print
#                   anything. Otherwise, you should print the
#                   classification and a newline.
# Returns:
#   a0 (int)        Classification
# Exceptions:
#   - If there are an incorrect number of command line args,
#     this function terminates the program with exit code 31
#   - If malloc fails, this function terminates the program with exit code 26
#
# Usage:
#   main.s <M0_PATH> <M1_PATH> <INPUT_PATH> <OUTPUT_PATH>
classify:

    # Prologue
    li t0, 5
    bne a0, t0, Invalid_argumet_number

    addi sp, sp, -48
    sw ra, 0(sp)
    sw s0, 4(sp)
    sw s1, 8(sp)
    sw s2, 12(sp)

    sw s3, 16(sp)           # s3 is used to store the number of rows and cols of m0
    sw s4, 20(sp)           # m1
    sw s5, 24(sp)           # input

    sw s6, 28(sp)
    sw s7, 32(sp)
    sw s8, 36(sp)           # Used to store the matrix

    sw s9, 40(sp)           # Store matrix h
    sw s10, 44(sp)
    
    mv s0, a0
    mv s1, a1
    mv s2, a2

    # Read pretrained m0
    li a0, 8
    jal ra, malloc
    beqz a0, malloc_failed
    mv s3, a0

    lw a0, 4(s1)         # m0's filename string
    addi a1, s3, 0
    addi a2, s3, 4          # Two pointers to the allocated memory
    jal ra, read_matrix

    mv s6, a0
    # Read pretrained m1
    li a0, 8
    jal ra, malloc
    beqz a0, malloc_failed
    mv s4, a0

    lw a0, 8(s1)         # m1's filename string
    addi a1, s4, 0
    addi a2, s4, 4          # Two pointers to the allocated memory
    jal ra, read_matrix

    mv s7, a0
    # Read input matrix
    li a0, 8
    jal ra, malloc
    beqz a0, malloc_failed
    mv s5, a0

    lw a0, 12(s1)          # input's filename string
    addi a1, s5, 0
    addi a2, s5, 4          # Two pointers to the allocated memory
    jal ra, read_matrix

    mv s8, a0

    # Compute h = matmul(m0, input)
    #--------------------------------------
    # s9 to store matrix h, s10 to store matrix o
    lw t0, 0(s3)            # m0's rows
    lw t1, 4(s5)            # input's cols
    mul a0, t0, t1
    slli a0, a0, 2          #-----Forget to convert to the true address.
    jal ra, malloc
    beqz a0, malloc_failed
    mv s9, a0               # malloc finished

    mv a0, s6
    lw a1, 0(s3)
    lw a2, 4(s3)
    mv a3, s8
    lw a4, 0(s5)
    lw a5, 4(s5)
    mv a6, s9
    jal ra, matmul

    # Compute h = relu(h)
    lw t0, 0(s3)            # m0's rows
    lw t1, 4(s5)            # input's cols
    mul a1, t0, t1
    mv a0, s9
    jal ra, relu

    # Compute o = matmul(m1, h)
    # First malloc memory space for s10
    lw t0, 0(s4)            # m1's rows
    lw t1, 4(s5)            # input's cols
    mul a0, t0, t1
    slli a0, a0, 2          #-----Forget to convert to the true address.
    jal ra, malloc
    beqz a0, malloc_failed
    mv s10, a0              # malloc finished

    mv a0, s7
    lw a1, 0(s4)
    lw a2, 4(s4)
    mv a3, s9
    lw a4, 0(s3)
    lw a5, 4(s5)
    mv a6, s10
    jal ra, matmul

    # Write output matrix o
    lw a0, 16(s1)           #-----Might be the last error
    mv a1, s10
    lw a2, 0(s4)
    lw a3, 4(s5)
    jal ra, write_matrix

    # Compute and return argmax(o)
    mv a0, s10
    lw t0, 0(s4)
    lw t1, 4(s5)
    mul a1, t0, t1
    jal ra, argmax
    mv s0, a0

    # If enabled, print argmax(o) and newline
    bne s2, zero, free_memory
    mv a0, s0
    jal ra, print_int
    li a0, '\n'
    jal ra, print_char
free_memory:
    # Free the memories
    mv a0, s3
    jal ra, free            # Free m0's rows and cols
    mv a0, s4
    jal ra, free            # Free m1's rows and cols
    mv a0, s5
    jal ra, free            # Free input's rows and cols
    mv a0, s6
    jal ra, free            # Free m0
    mv a0, s7
    jal ra, free            # Free m1
    mv a0, s8
    jal ra, free            # Free input
    mv a0, s9
    jal ra, free            # Free h
    mv a0, s10
    jal ra, free            # Free o

    mv a0, s0               # Return a0
    # Epilogue
    
    lw ra, 0(sp)
    lw s0, 4(sp)
    lw s1, 8(sp)
    lw s2, 12(sp)
    lw s3, 16(sp)
    lw s4, 20(sp)
    lw s5, 24(sp)
    lw s6, 28(sp)
    lw s7, 32(sp)
    lw s8, 36(sp)
    lw s9, 40(sp)
    lw s10, 44(sp)

    addi sp, sp, 48

    jr ra

malloc_failed:
    li a0, 26
    j exit

Invalid_argumet_number:
    li a0, 31
    j exit

## Hoo-Yeah! Project 2 Finished!
