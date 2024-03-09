#include "transpose.h"

/* The naive transpose function as a reference. */
void transpose_naive(int n, int blocksize, int *dst, int *src) {
    for (int x = 0; x < n; x++) {
        for (int y = 0; y < n; y++) {
            dst[y + x * n] = src[x + y * n];
        }
    }
}

/* Implement cache blocking below. You should NOT assume that n is a
 * multiple of the block size. */
void transpose_blocking(int n, int blocksize, int *dst, int *src) {
    // YOUR CODE HERE
	int row = 0, col = 0;
	for (row = 0; row < n; row += blocksize) {
		for (col = 0; col < n; col += blocksize) {
			for (int y = col; y < col + blocksize && y < n; y++) {
				for (int x = row; x < row + blocksize && x < n; x++) {
					dst[y + x * n] = src[x + y * n];
				}
			}
		}
	}
}

