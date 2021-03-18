#include <stdio.h>;
#define x 0.1

//Recursive descent + reсursive return
double recurSum(int length, double F, double sum, int i) {
	double curF = F;
	if (length > i) {
		i++;
		F = -F * x * (2 * i - 3) / (2 * i - 2);
		sum = recurSum(length, F, sum, i);
	}
	sum += curF;
	return sum;
}

int main() {
	double F = 1, sum = 0;
	int len;
	printf_s("Input length of recursion (integer): ");
	scanf_s("%d", &len);
	sum = recurSum(len, F, sum, 1);
	printf_s("Result: %f\n", sum);
}