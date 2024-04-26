import numc as nc

A = nc.Matrix(2, 3, 4);
A.set(1, 2, 5);
a = A.get(1, 2);
b = A.get(1, 1);
print(f"a = {a}, b = {b}");
c = A.set(3, 4, 1);

