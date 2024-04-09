from numc import Matrix

a = Matrix(4, 2, 1);
b = Matrix(4, 2, 2);

print("First Time");
print(a + b);

a = Matrix(2, 3);
b = Matrix(3, 2);
c = Matrix(1, 2, 3);
d = Matrix(1, 2, 4);

print("1D:");
print(c + d);
print("2D, but different dimension:");
print(a + b);

