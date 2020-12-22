#include <stdio.h>
#include <math.h>
#define n 10

int main() {
   float X[n];
   float Y[n];
   float A = 5;
   X[0] = A;
   Y[0] = 1;
   for (int i = 0; i < n; i++) {
       float sum = 0;
       for (int k = 0; k < n - 2; k++) {
           sum += pow((1 - X[i]), k);
        };
       if (i + 1 < n) {
           Y[i + 1] = Y[i] * sum;
           X[i + 1] = X[i] * sum;
           printf("%f\n", Y[i + 1]);
           printf("%f\n", X[i + 1]);
       }
   }
   return 0;
};