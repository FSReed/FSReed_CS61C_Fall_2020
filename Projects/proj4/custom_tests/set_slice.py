import numc as nc

A = nc.Matrix(4, 5, 66.6);
A[0, 0:3] = [1, 2, 3]
A[1, 0] = 6
print(A)

B = A[1:4, 2:4]
print(B);
B[2, 2] = 1000
print(A)

C = A[1, 1:5];
print(C)
C[1:3] = [7, 8]
print(A)

D = A[1:4, 1:5]
D[1:3, 0:3] = [[12, 13, 14], [17, 18, 19]]
print(A)

A[0:2, 0:2] = [[1, 2], [1, [1, 2]]]

