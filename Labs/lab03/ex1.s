.data
.word 2, 4, 6, 8
n: .word 9

.text
main:
    add t0, x0, x0
    addi t1, x0, 1
    la t3, n
    lw t3, 0(t3)
fib:
    beq t3, x0, finish
    add t2, t1, t0
    mv t0, t1
    mv t1, t2
    addi t3, t3, -1
    j fib
finish:
    addi a0, x0, 1
    addi a1, t0, 0
    ecall # print integer ecall
    addi a0, x0, 0xA
    ecall # terminate ecall
# n stands for the n'th fib number. The "0th" fib number is 0.
# When return in label "finish", we are returning the value in t0, which is the n'th fib number.
# Set a break point at lw t3, 0(t3), and manually change the value of t3 to be 0x0000000d,
# Then run the rest of the codes, we can get the 13th fib number is 233.