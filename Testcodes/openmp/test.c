/* Use `gcc -o [filename] -fopenmp test.c` to compile
   Then use `./[filename]` to execute */

#include <stdio.h>
#include <omp.h>

int main() {
    	const int THREAD = 4;
	omp_set_num_threads(THREAD);
	printf("There are %d threads working now:\n", THREAD);
	#pragma omp parallel for
	for (int i = 0; i < 20; i++) {
		printf("thread = %d\n", omp_get_thread_num());
	}
	return 0;
}

