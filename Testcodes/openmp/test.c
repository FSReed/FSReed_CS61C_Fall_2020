/* Use `gcc -o [filename] -fopenmp test.c` to compile
   Then use `./[filename]` to execute */

#include <stdio.h>
#include <omp.h>

int main() {
	omp_set_num_threads(4);
	#pragma omp parallel for
	for (int i = 0; i < 10; i++) {
		printf("thread = %d\n", omp_get_thread_num());
	}
	return 0;
}
