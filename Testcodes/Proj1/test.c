#include <stdio.h>
#include <stdlib.h>
#include <inttypes.h>
#include <string.h>

int main() {
	FILE *fp = fopen("sample.ppm", "r");
	char buff[20];
	uint8_t number;
	int num1, num2;
	fscanf(fp, "%s", buff);
	int result1 = fscanf(fp, "%d%d", &num1, &num2);
	int result2 = fscanf(fp, "%hhu", &number);
	printf("%d %d %d\n", num1, num2, number);
	printf("result1 = %d, result2 = %d\n", result1, result2);
	
	uint32_t R, G, B;
//	uint32_t G, B;
	fscanf(fp, "%d%d%d", &R, &G, &B);
	printf("%d %d %d\n", R, G, B);
	printf("%d\n", number);
	
	uint8_t r1, r2, r3;
	r1 = (uint8_t)R;
	r2 = (uint8_t)G;
	r3 = (uint8_t)B;
	printf("%d %d %d\n", r1, r2, r3);
	
	uint8_t result;
	uint8_t param = 1;
	result = 255 + param;
	printf("%d\n", result);
	return 0;
}
