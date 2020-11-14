#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define START1_I 11
#define START1_J 80
#define END1_I 0
#define END1_J 80

#define START2_I 12
#define START2_J -1
#define END2_I 23
#define END2_J 0

void gotoxy(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printMtx(int i, int j) {
    gotoxy(j, i);
    putchar('X');
}

int main() {
    int cur_i1 = START1_I;
    int cur_j1 = START1_J;
    int cur_i2 = START2_I;
    int cur_j2 = START2_J;
    while ((cur_i1 != END1_I || cur_j1 != END1_J) && (cur_i2 != END2_I || cur_j2 != END2_J)) {
        if (cur_i1 % 2 != 0) {
            if (cur_j1 != 0) {
                cur_j1--;
                cur_j2++;
            }
            else {
                cur_i1--;
                cur_i2++;
            }
        }
        else {
            if (cur_j1 != 79) {
                cur_j1++;
                cur_j2--;
            }
            else {
                cur_i1--;
                cur_i2++;
            }
        }
        printMtx(cur_i1, cur_j1);
        printMtx(cur_i2, cur_j2);
        Sleep(7);
    }
    getchar();
    return 0;
}