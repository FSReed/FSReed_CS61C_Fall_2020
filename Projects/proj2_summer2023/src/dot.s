.globl dot

.text
# =======================================================
# FUNCTION: Dot product of 2 int arrays
# Arguments:
#   a0 (int*) is the pointer to the start of arr0
#   a1 (int*) is the pointer to the start of arr1
#   a2 (int)  is the number of elements to use
#   a3 (int)  is the stride of arr0
#   a4 (int)  is the stride of arr1
# Returns:
#   a0 (int)  is the dot product of arr0 and arr1
# Exceptions:
#   - If the number of elements to use is less than 1,
#     this function terminates the program with error code 36
#   - If the stride of either array is less than 1,
#     this function terminates the program with error code 37
# =======================================================
dot:
    ebreak
    li t0, 1
    blt a2, t0, invalid_element
    blt a3, t0, invalid_stride
    blt a4, t0, invalid_stride
    
    # Prologue
    addi sp, sp, -8
    sw s0, 0(sp)
    sw s1, 4(sp)  # 

    li t0, 0  # The sum
    li t1, 0  # The number of operations now
    mv t2, a0  # Used to store the current position of arr0
    mv t3, a1  # Used to store the current position of arr1
    li t4, 0  # Used to store the current product
    slli a3, a3, 2
    slli a4, a4, 2  # Convert a3 and a4 to the stride in bytes
loop_start:
    beq t1, a2, loop_end
    
    lw s0, 0(t2)
    lw s1, 0(t3)  # Now s0 and s1 are elements ready for operating the real numbers
    
    mul t4, s0, s1  # Calculate the current product
    addi t1, t1, 1  # Increase the count of operation by 1
    add t0, t0, t4  # Update the return sum value
    
    add t2, t2, a3
    add t3, t3, a4  # Update the next position to operate
    j loop_start
    
loop_end:
    mv a0, t0
    
    # Epilogue
    lw s0, 0(sp)
    lw s1, 4(sp)
    addi sp, sp, 8

    jr ra

invalid_element:
    li, a0, 36
    j exit
invalid_stride:
    li a0, 37
    j exit