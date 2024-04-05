/* Use `gcc -o [filename] -fopenmp race.c` to compile
   Then use `./[filename]` to execute */

#include <stdio.h>
#include <omp.h>

void main() {
    const int NUM = 100000;
    const int THREAD = 4; // This would cause the race condition.

    int sum = 0;
    omp_set_num_threads(THREAD);
#pragma omp parallel for
    for (int i = 0; i < NUM; i++) {
	sum += 1;
    }
    printf("The expected result should be %d, and we get sum = %d\n", NUM, sum);
    return;
}
