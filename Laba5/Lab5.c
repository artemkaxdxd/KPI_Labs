#include <stdio.h>
#define N 7
#define M 8

int A[N][M] = {
		{ 2, 1, 3, 5, 6, 4, 9, 8, },
		{ 3, 6, 2, 6, 2, 3, 7, 1, },
		{ 6, 4, 1, 3, 3, 5, 1, 5, },
		{ 4, 2, 5, 8, 7, 1, 3, 3, },
		{ 5, 7, 4, 1, 4, 6, 2, 6, },
		{ 1, 9, 7, 2, 5, 9, 6, 4, },
		{ 7, 3, 6, 9, 8, 8, 5, 2, }, };

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
		int j, n =7;
		for (int i = 0; i < n; i++) {
			A[0][col] = A[i][col];
			j = i;
			while (A[0][col] < A[j - 1][col]) {
				A[j][col] = A[j - 1][col];
				j = j - 1;
			}
			A[j][col] = A[0][col];
		}
		col++;
	}
	printf("\nSorted matrix: \n");
	printM();
	return 0;
}