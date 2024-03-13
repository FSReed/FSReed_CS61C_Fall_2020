#include <stdio.h>
#include <stdlib.h>

int main() {
	const int G = 1024 * 1024 * 1024;
	for (int n = 0;; n++) {
		char *p = malloc(G * sizeof(char));
		if (p == NULL) {
			fprintf(stderr,
					"Failed to malloc >  %g TiBytes\n", n / 1000.0);
			return 1;
		}
	}
	return 0;
}

