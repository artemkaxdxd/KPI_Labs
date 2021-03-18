#include <stdio.h>;
#define x 0.1

//Check (loop)
int main() {
	double sum = 1, F;
	int len;
	printf_s("Input length of recursion (integer): ");
	scanf_s("%d", &len);
	for (int i = 2; i <= len; i++) {
		F = -F * 0.1 * (2 * i - 3) / (2 * i - 2);
		sum += F;
	}
	printf_s("Result: %f\n", sum);
}