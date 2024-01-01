.globl argmax

.text
# =================================================================
# FUNCTION: Given a int array, return the index of the largest
#   element. If there are multiple, return the one
#   with the smallest index.
# Arguments:
#   a0 (int*) is the pointer to the start of the array
#   a1 (int)  is the # of elements in the array
# Returns:
#   a0 (int)  is the first index of the largest element
# Exceptions:
#   - If the length of the array is less than 1,
#     this function terminates the program with error code 36
# =================================================================
argmax:
    # Prologue
    addi sp, sp, -4
    sw s0, 0(sp)  # Used to store the number 1.
    li s0, 1

    bge a1, s0, loop_start
    li a0, 36
    j exit
loop_start:
    li t0, 0  # The position of the max_value
    li t1, 0  # The current position
    lw t2, 0(a0)  
    addi t2, t2, 1  # The max value now, but added 1!
    mv t3, t2  # The current value
    
loop_continue:
    addi a0, a0, 4
    addi a1, a1, -1  # Direct to the next position of the array
    blt a1, s0, loop_end
    addi t1, t1, 1
    lw t3, 0(a0)
    blt t3, t2, loop_continue
    mv t0, t1  # Update the position of the max value now
    mv t2, t3
    addi t2, t2, 1  # Upadte t2
    j loop_continue
    
loop_end:
    # Epilogue
    lw s0, 0(sp)
    addi sp, sp, 4
    
    mv a0, t0
    jr ra
