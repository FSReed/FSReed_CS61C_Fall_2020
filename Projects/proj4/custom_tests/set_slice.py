import numc as nc

A = nc.Matrix(4, 5, 1);
print(A[2:4, 3])
A[2:4, 3] = [12.9, 13.3]
print(A)

