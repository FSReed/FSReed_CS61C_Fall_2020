#include <stdio.h>
#include <omp.h>

void main() {
    const int NUM = 100000; // This would cause the race condition.
    const int THREAD = 4;
    int sum = 0;
    omp_set_num_threads(THREAD);
#pragma omp parallel for
    for (int i = 0; i < NUM; i++) {
	sum += 1;
    }
    printf("sum = %d\n", sum);
    return;
}
