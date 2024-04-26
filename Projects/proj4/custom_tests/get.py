import numc as nc

A = nc.Matrix(2, 3, 3);
a = A.get(1, 1);
print(a);

B = nc.Matrix(2, 3, 4);
b = B.get(3, 4);
