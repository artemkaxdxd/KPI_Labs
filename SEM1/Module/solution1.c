#include <stdio.h>
#define n 10

int main() {
    float X[n];
    float Y[n];
    float A = 5;
    X[0] = A;
    Y[0] = 1;
    double power = 1;
    for (int i = 0; i < n - 2; i++) {
        float sum = 0;
        power *= (1 - X[i]);
        for(int k = 1; k <= n-2; k++){
            sum += power;
        }
        if (i + 1 < n) {
            Y[i + 1] = Y[i] * sum;
            X[i + 1] = X[i] * sum;
            printf("%f\n", Y[i + 1]);
            printf("%f\n", X[i + 1]);
        }
    }
    return 0;
};