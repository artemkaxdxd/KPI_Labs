#include <stdio.h>;
#define x 0.1

//Recursive descent
double recurSum(int length, double F, double sum, int i) {
	i++;
	sum += F;
	F = -F * x * (2 * i - 3) / (2 * i - 2);
	if (length + 1 != i) 
		sum = recurSum(length, F, sum, i);
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