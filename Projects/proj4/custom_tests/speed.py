import numc as nc
import time

SIZE = 2000;
print(f"Size of the square matrix is {SIZE} * {SIZE}");

A = nc.Matrix(SIZE, SIZE, 2.3);
B = nc.Matrix(SIZE, SIZE, 3.4);

start = time.time();
C = A + B;
stop = time.time();

print(f"A + B spends {stop - start} seconds");

start = time.time();
C = A * B;
stop = time.time();

print(f"A * B spends {stop - start} seconds");

start = time.time();
C = A ** 5;
stop = time.time();

print(f"A ** 5 spends {stop - start} seconds");

