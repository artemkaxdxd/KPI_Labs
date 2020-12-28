#include <stdio.h>
#define N 20

int main() {
	float arr[N];
	float X = 5.3;
	arr[0] = X;
	float first = 1; // -1^k+1
	float second = 1; // x^2k+1
	float Xcur = 1;
	float sum = 0;
	float division = 1;
	for (int k = 1; k < N; k++) {
		first *= -1;
		Xcur *= X; // x^k
		division = (Xcur * Xcur * X) / (2 * k + 1); // X^2k+1 / 2k+1
		sum += (-1) * first * division;
		arr[k] = sum;
		printf("%f\n", arr[k]);
	}
	return 0;
}