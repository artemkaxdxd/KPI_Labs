#include <stdio.h>
#define N 7
#define M 8

int A[N][M] = {
		{ 1, 7, 3, -5, 6, 7, 4, 7, },
		{ 2, 6, 4, -6, 2, 3, 7, 1, },
		{ 3, 5, 3, -3, 3, 5, 1, 5, },
		{ 4, 4, 2, -7, 7, 1, 3, 3, },
		{ 5, 3, 1, -1, 4, 6, 2, 6, },
		{ 6, 2, 2, -2, 5, 2, 6, 4, },
		{ 7, 1, 1, -4, 1, 4, 5, 2, }, };

void printM() {
	for (int R = 0; R < N; R++) {
		for (int C = 0; C < M; C++) {
			printf("%d ", A[R][C]);
		}
		printf("\n");
	}
}

int main() {
	printf("Initial matrix: \n");
	printM();
	int col = 0;
	while(col < M) {
		int j, n = 7, key;
		for (int i = 1; i < n; i++) {
			key = A[i][col];
			j = i - 1;
			while (j >= 0 && A[j][col] > key) {
				A[j + 1][col] = A[j][col];
				j--;
			}
			A[j + 1][col] = key;
		}
		col++;
	}
	printf("\nSorted matrix: \n");
	printM();
	return 0;
}