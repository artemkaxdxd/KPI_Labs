#include <stdio.h>

#define M 10
#define N 8

int matrix[M][N] = {
        { 10, 20, 30, 40, 50, 60, 70, 80 },
        { 9, 19, 29, 39, 49, 59, 69, 79 },
        { 8, 18, 28, 38, 48, 58, 68, 78 },
        { 7, 17, 27, 37, 47, 57, 67, 77 },
        { 6, 16, 26, 36, 46, 56, 66, 76 },
        { 5, 15, 25, 35, 45, 55, 65, 75 },
        { 4, 14, 24, 34, 44, 54, 64, 74 },
        { 3, 13, 23, 33, 43, 53, 63, 73 },
        { 2, 12, 22, 32, 42, 52, 62, 72 },
        { 1, 11, 21, 31, 41, 51, 61, 71 } };

int main(void) {
    int col = 0, key;
    printf("Input your key: ");
    scanf_s("%d", &key);
    while (col < 7) {
        int low = 0, high = 9, mid = (low + high) / 2;
        while (low <= high) {
            if (matrix[mid][col] == key) {
                printf("Found key at %d, %d\n", col, mid);
                break;
            }
            else if (matrix[mid][col] > key) {
                low = mid + 1;
            }
            else if (matrix[mid][col] < key) {
                high = mid - 1;
            }
            mid = (low + high) / 2;
        }
        col++;
    }
    return 0;
}