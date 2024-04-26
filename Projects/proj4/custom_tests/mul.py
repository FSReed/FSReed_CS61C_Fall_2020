import numc as nc

A = nc.Matrix([[1, 2], [2, 3]]);
B = nc.Matrix([[1, 1], [2, 1]]);
print(f"2*2 Matrices: {A * B}")

A = nc.Matrix([[1, 2, 3], [2, 3, 4]]);
B = nc.Matrix([[1, 2], [2, 3], [3, 4]]);
print(f"2*3 and 3*2 Matrix: {A * B}")

A = nc.Matrix(2, 3);
B = nc.Matrix(2, 3);
print(f"Wrong Dimension test:\n {A * B}");

