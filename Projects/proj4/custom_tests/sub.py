import numc as nc

A = nc.Matrix([[1, 2, 3], [4, 5, 6]]);
B = nc.Matrix(2, 3, 3);
print(f'A - B = {A - B}');

C = nc.Matrix(1, 3);
D = nc.Matrix(1, 2);
print(C + D)

