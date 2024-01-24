.globl write_matrix

.text
# ==============================================================================
# FUNCTION: Writes a matrix of integers into a binary file
# FILE FORMAT:
#   The first 8 bytes of the file will be two 4 byte ints representing the
#   numbers of rows and columns respectively. Every 4 bytes thereafter is an
#   element of the matrix in row-major order.
# Arguments:
#   a0 (char*) is the pointer to string representing the filename
#   a1 (int*)  is the pointer to the start of the matrix in memory
#   a2 (int)   is the number of rows in the matrix
#   a3 (int)   is the number of columns in the matrix
# Returns:
#   None
# Exceptions:
#   - If you receive an fopen error or eof,
#     this function terminates the program with error code 27
#   - If you receive an fclose error or eof,
#     this function terminates the program with error code 28
#   - If you receive an fwrite error or eof,
#     this function terminates the program with error code 30
# ==============================================================================
write_matrix:

    # Prologue
    addi sp, sp, -20
    sw ra, 0(sp)
    sw s0, 4(sp)
    sw s1, 8(sp)
    sw s2, 12(sp)
    sw s3, 16(sp)

    mv s0, a0
    mv s1, a1
    mv s2, a2
    mv s3, a3

    # Open the file
    mv a0, s0
    li a1, 1            # Write-only code is 1
    jal ra, fopen
    li t0, -1
    beq a0, t0, fopen_failed
    mv s0, a0           # Now s0 stores the file descriptor

    # Write the number of rows and cols into the file
    addi sp, sp, -8
    sw s2, 0(sp)
    sw s3, 4(sp)

    mv a0, s0
    mv a1, sp
    li a2, 2
    li a3, 4
    jal ra, fwrite
    li t0, 2
    bne a0, t0, fwrite_failed

    # Restore sp
    addi sp, sp, 8

    # Write the matrix into the file
    mul s2, s2, s3
    mv a0, s0
    mv a1, s1
    mv a2, s2
    li a3, 4
    jal ra, fwrite
    bne a0, s2, fwrite_failed

    # Close the file
    mv a0, s0
    jal ra, fclose
    bnez a0, fclose_failed

    # Epilogue
    lw ra, 0(sp)
    lw s0, 4(sp)
    lw s1, 8(sp)
    lw s2, 12(sp)
    lw s3, 16(sp)
    addi sp, sp, 20

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

fwrite_failed:
    li a0, 30
    j exit
