import numc as nc

A = nc.Matrix(4, 5, 1);
print(A[2:4, 3])
A[2:4, 3] = [12.9, 13.3]
A[0, 2] = 11.6
print(A)

B = A[1:4, 2:4]
print(B);
B[2, 2] = 100
print(A)

