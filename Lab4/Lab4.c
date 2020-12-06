#include <stdio.h>

#define M 10
#define N 8

int matrix[M][N] = {
        {  0, 3, 6, 9, 12, 16, 19, 22 },
        {  0, 3, 6, 9, 12, 16, 19, 22 },
        {  0, 3, 6, 8, 12, 16, 19, 22 },
        { -1, 3, 5, 8, 12, 15, 18, 21 },
        { -1, 2, 5, 8, 11, 14, 18, 21 },
        { -1, 2, 5, 8, 11, 14, 18, 21 },
        { -1, 2, 5, 7, 11, 14, 17, 20 },
        { -2, 1, 4, 7, 10, 14, 17, 20 },
        { -2, 1, 4, 7, 10, 13, 17, 20 },
        { -2, 1, 4, 7, 10, 13, 17, 20 } };

int main(void) {
    int col = 0, key;
    printf("Input your key: ");
    scanf_s("%d", &key);
    if (key < -2 || key > 22) {
        printf("Your key doesn't exist in matrix");
        return 0;
    }
    while (col < 8) {
        int low = 0, high = 9, mid = (low + high) / 2;
        while (low <= high) {
            if (matrix[mid][col] == key) {
                printf("Found key at coord [%d, %d]\n", col, mid);
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