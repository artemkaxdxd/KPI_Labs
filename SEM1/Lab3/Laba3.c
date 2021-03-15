#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <windows.h>

#define ST_1I 11
#define ST_1J 80
#define END_1I 0
#define END_1J 80

#define ST_2I 12
#define ST_2J -1
#define END_2I 23
#define END_2J 0

int mtx[24][80] = { 0 };

void gotoXY(int x, int y) {
    COORD coord;
    coord.X = x;
    coord.Y = y;
    SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}

void printMtx(int i, int j) {
    gotoXY(j, i);
    putchar('#');
}

int main() {
    int cur_i1 = ST_1I;
    int cur_j1 = ST_1J;
    int cur_i2 = ST_2I;
    int cur_j2 = ST_2J;
    while ((cur_i1 != END_1I || cur_j1 != END_1J) && (cur_i2 != END_2I || cur_j2 != END_2J)) {
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
        mtx[cur_i1][cur_j1] = 1;
        mtx[cur_i2][cur_j2] = 1;
        printMtx(cur_i1, cur_j1);
        printMtx(cur_i2, cur_j2);
        Sleep(7);
    }
    getchar();
    return 0;
}