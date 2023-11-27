#include <stdio.h>

int main() {
	printf("%d\n", sizeof(int));
	int a = 3;
	printf("%p\n", &a);
	int b = 3;
	printf("%p\n", &b);
	int c = 3;
	printf("%p\n", &c);

	int* p, *q;
	printf("sizeof p: %d\n", sizeof(p));
 	printf("%p\n%p\n", &p, &q);
	return 0;
}
