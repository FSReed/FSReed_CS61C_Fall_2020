.globl factorial

.data
n: .word 8

.text
main:
    la t0, n
    lw a0, 0(t0)
    jal factorial

    addi a1, a0, 0
    addi a0, x0, 1
    ecall # Print Result

    addi a1, x0, '\n'
    addi a0, x0, 11
    ecall # Print newline

    addi a0, x0, 10
    ecall # Exit

factorial:
    # YOUR CODE HERE
    beq, a0, zero, exit
    # else:
    addi t0, a0, 0
    addi a0, a0, -1     # Prepare for next call of factorial
    addi sp, sp, -8
    sw t0, 0(sp)
    sw ra, 4(sp)
    jal factorial
    lw t0, 0(sp)
    lw ra, 4(sp) # Save and restore t0, ra
    addi sp, sp, 8      # Restore sp
    mul a0, t0, a0
    ret
exit:
    addi a0, a0, 1      # Return 1
    ret