import numc as nc
import time

SIZE = 5000;
print(f"Size of the square matrix is {SIZE} * {SIZE}");

A = nc.Matrix(SIZE, SIZE, 2.3);
B = nc.Matrix(SIZE, SIZE, 3.4);

start = time.time();
C = A + B;
stop = time.time();

print(f"A + B spends {stop - start} seconds");

start = time.time();
C = A - B;
stop = time.time();

print(f"A - B spends {stop - start} seconds");

start = time.time();
C = abs(A);
stop = time.time();

print(f"abs(A) spends {stop - start} seconds");

start = time.time();
C = A * B;
stop = time.time();

print(f"A * B spends {stop - start} seconds");

