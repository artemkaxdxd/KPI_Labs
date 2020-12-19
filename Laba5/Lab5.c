#include <stdio.h>
#define N 7
#define M 8

int matrix[N][M] = { 
			{ 2, 1, 3, 5, 6, 4, 9, 8, },
			{ 3, 6, 2, 6, 2, 3, 7, 1, },
			{ 6, 4, 1, 3, 3, 5, 1, 5, },
			{ 4, 2, 5, 8, 7, 1, 3, 3, },
			{ 5, 7, 4, 1, 4, 6, 2, 6, },
			{ 1, 9, 7, 2, 5, 9, 6, 4, },
			{ 7, 3, 6, 9, 8, 8, 5, 2, }, };

int main() {
	for (int R = 0; R < N; R++) {
		for (int C = 0; C < M; C++) {
			printf("%d ", matrix[R][C]);
		}
		printf("\n");
	}
	int i, j, col = 0;
	while(col < N) {
        for (int i = 1; 1 < N; i++) {
            // add solution
        }
    }
	return 0;
}