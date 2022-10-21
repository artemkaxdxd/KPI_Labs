#include <stdio.h>
#include <math.h>

#define M_PI 3.14159265359

float functionA(float x, float y, float z) {
    return (1 + y) * ((x + y / (pow(x, 2) - 1)) / (pow(y, x - 2) + 1 / (pow(x, 2) + 4)));
}

float functionB(float x, float y, float z) {
    return x * (sin(atan(z)) + pow(tan(y), 2));
}

int main() {
    float eps = 10e-6;
    float x, y, z;
    printf("X: ");
    scanf_s("%f", &x);
    printf("Y: ");
    scanf_s("%f", &y);
    printf("Z: ");
    scanf_s("%f", &z);

    if (x == 1) {
        printf("No value for A (ODZ: X != +-1)\n");
    }
    else if (x == -1) {
        printf("No value for A (ODZ: X != +-1)\n");
    }
    else {
        float resultA = functionA(x, y, z);
        printf("Calculated value for A: %f\n", resultA);
    }

    float modded = fmod(y * (2 / M_PI), 2);
    if (modded < 1 + eps) {
        if (modded > 1 - eps) {
            printf("No value for B (-PI/2 - P*N < x < PI/2 + P*N)\n");
            return 0;
        }
    }

    float resultB = functionB(x, y, z);
    printf("Calculated value for B: %f\n", resultB);

    return 0;
}