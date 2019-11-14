#include <stdio.h>
#pragma warning(disable: 4996)
int main(void) {
	int a = 3, b = 9.5, c = 9 / 4;
	float p = 3 * 5 / 2, q = 6.5;
	char x[7] = { 0, 6, 5, 2, 4,3,1 }, k;
	char z[3][5] = { {68,60,56},{24,55,67},{35,44,32} };
	char* y = x + 1;
	char* r = *z + 2;
	printf("%d", ~a);
	return 0;
}