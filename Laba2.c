#include <stdio.h>
#include <math.h>

double way1(int n) { // Варіант 1
	double S = 0;
	int counter = 0;
	double power = 1;
	for (int i = 1; i <= n; i++) {
		power *= 3;
		counter++;
		double sum = power * log(i + 1);
		counter += 3; // * + log + (+) = 3 operations
		double res2 = 1;
		for (int j = 1; j <= i; j++) {
			res2 *= (2 * j + 1);
			counter += 3; // * + ((*) + (+)) = 3 operations
		}
		S += (sum / res2);
		counter += 2; // (+) + / = 2 operations
	}
	printf("Operations in way1 : %d \n", counter);
	return S;
}

double way2(int n) { // Варіант 2
	double sum = 0;
	double cache1 = 1;
	int counter = 0;
	double power = 1;
	for (int i = 1; i <= n; i++) {
		power *= 3;
		counter++;
		double res1 = power * log(i + 1);
		counter += 3; // * + log + (+)= 3 operations
		cache1 *= (2 * i + 1);
		counter += 3; // * + ((*) + (+)) = 3 operations
		sum += res1 / cache1;
		counter += 2; // (+) + / = 2 operations
	}
	printf("Operations in way2 : %d \n", counter);
	return sum;
}

int main() {
	int n = 0;
	printf("Input your n : ");
	scanf_s("%d", &n);
	double res1 = way1(n);
	printf("Result for way1 : %.7f \n", res1);
	double res2 = way2(n);
	printf("Result for way2 : %.7f \n", res2);
	return 0;
}