.globl relu

.text
# ==============================================================================
# FUNCTION: Performs an inplace element-wise ReLU on an array of ints
# Arguments:
#   a0 (int*) is the pointer to the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   None
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# ==============================================================================
relu:
    ebreak
    # Prologue
    addi sp, sp, -4
    sw s0, 0(sp)
    
    li s0, 1
    bge a1, s0, loop_start  # If the array has no element, raise an exception with an exit code 36.
    li a0, 36
    j exit
loop_start:
    beq a1, zero, loop_end
    lw t0, 0(a0)
    bge t0, zero, loop_continue
    mv t0, zero
loop_continue:
    sw t0, 0(a0)
    addi a0, a0, 4
    addi a1, a1, -1
    j loop_start
loop_end:
    # Epilogue
    lw s0, 0(sp)
    addi sp, sp, 4
    
    jr ra
