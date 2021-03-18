#include <stdio.h>;
#define x 0.1

//Recursive return
double recurSum(double F, double* sum, int i) {
	if (i > 1) {
		F = recurSum(F, sum, i - 1);
		F = -F * x * (2 * i - 3) / (2 * i - 2);
		*sum += F;
	}
	else *sum = F;
	return F;
}

int main() {
	double F = 1, sum = 0;
	int i;
	printf_s("Input length of recursion (integer): ");
	scanf_s("%d", &i);
	F = recurSum(F, &sum, i);
	printf_s("Result: %f\n", sum);
}