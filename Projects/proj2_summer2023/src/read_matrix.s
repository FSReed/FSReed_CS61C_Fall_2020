.globl read_matrix

.text
# ==============================================================================
# FUNCTION: Allocates memory and reads in a binary file as a matrix of integers
#
# FILE FORMAT:
#   The first 8 bytes are two 4 byte ints representing the # of rows and columns
#   in the matrix. Every 4 bytes afterwards is an element of the matrix in
#   row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is a pointer to an integer, we will set it to the number of rows
#   a2 (int*)  is a pointer to an integer, we will set it to the number of columns
# Returns:
#   a0 (int*)  is the pointer to the matrix in memory
# Exceptions:
#   - If malloc returns an error,
#     this function terminates the program with error code 26
#   - If you receive an fopen error or eof,
#     this function terminates the program with error code 27
#   - If you receive an fclose error or eof,
#     this function terminates the program with error code 28
#   - If you receive an fread error or eof,
#     this function terminates the program with error code 29
# ==============================================================================
read_matrix:

    # Prologue
    addi sp, sp, -28
    sw s0, 0(sp)
    sw s1, 4(sp)
    sw s2, 8(sp)
    sw s3, 12(sp)       # The pointer to the matrix in memory
    sw s4, 16(sp)       # The actual space of memory for the matrix
    sw s5, 20(sp)
    sw ra, 24(sp)
    mv s0, a0
    mv s1, a1
    mv s2, a2

    mv a0, s0
    li a1, 0
    jal ra fopen
    li t0, -1
    beq a0, t0, fopen_failed
    mv s0, a0           # Now s0 is the file descriptor

    li a0, 4
    jal ra, malloc
    beq a0, zero, malloc_failed
    mv s5, a0           # Use s5 to read the first 2 numbers

    mv a0, s0
    mv a1, s5
    li a2, 4
    jal ra fread
    li t0, 4
    bne a0, t0, fread_failed
    lw t0, 0(s5)
    sw t0, 0(s1)        # Store the row number in the corresponding address

    mv a0, s0
    mv a1, s5
    li a2, 4
    jal ra fread
    li t0, 4
    bne a0, t0, fread_failed
    lw t0, 0(s5)
    sw t0, 0(s2)        # Store the col number in the corresponding address
    
    lw s1, 0(s1)
    lw s2, 0(s2)        # Now s1 and s2 stores the real number of rows and cols, not addresses anymore
    mul s4, s1, s2
    slli s4, s4, 2      # Allocate space for the matrix
    mv a0, s4
    jal ra malloc
    beq a0, zero, malloc_failed
    mv s3, a0           # s3 stores the address of return matrix

    mv a0, s0
    mv a1, s3
    mv a2, s4
    jal ra fread
    bne a0, s4, fread_failed

    mv a0, s0
    jal ra, fclose
    bne a0, zero, fclose_failed

    # Epilogue

    lw s0, 0(sp)
    lw s1, 4(sp)
    lw s2, 8(sp)
    lw s3, 12(sp)
    lw s4, 16(sp)
    lw s5, 20(sp)
    lw ra, 24(sp)
    addi sp, sp, 28
    mv a0, s3
    jr ra

malloc_failed:
    li a0, 26
    j exit

fopen_failed:
    li a0, 27
    j exit

fclose_failed:
    li a0, 28
    j exit

fread_failed:
    li a0, 29
    j exit
