.globl abs

.text
# =================================================================
# FUNCTION: Given an int return its absolute value.
# Arguments:
#   a0 (int*) is a pointer to the input integer
# Returns:
#   None
# =================================================================
abs:
  ebreak
  # Load number from memory
  lw t0 0(a0)
  bge t0, zero, done

  # Negate a0
  sub t0, x0, t0

  # Store number back to memory
  sw t0 0(a0)

done:
  ret
