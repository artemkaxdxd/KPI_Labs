# include <stdio.h>

float function1(float x) {
    return -14 * x - 20;
}

float function2(float x) {
    return 13 * x * x / 11 - 6;
}

int main() {
    float x;
    for (int i = 0; i < 10; i++) {
        printf("Input any x value:");
        scanf_s("%f", &x);
        printf("result: \n");
        if (x > -21) {
            if (x <= 3) {
                printf("%f \n", function1(x));
            }
            else if (x > 12) {
                printf("%f \n", function1(x));
            }
            else {
                printf("X is out of bounds \n");
            }
        }
        else {
            if (x <= -41) {
                printf("%f \n", function2(x));
            }
            else {
                printf("X is out of bounds \n");
            }
        }
        printf("\n");
    }
    return 0;
}