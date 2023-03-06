#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h> // to use the clock function

double my_pow(double x);

double x_min = 0;
double x_max = 1;

int main()
{
    clock_t start1, end1, start2, end2;
    double x, z1, z2;
    double y = 100.0;
    start1 = clock();

    for (int i = 0; i < 100000000; i++)
    {
        x = (double)rand() / RAND_MAX * (x_max - x_min) + x_min;
        z1 = pow(x, y);
    }
    end1 = clock();

    start2 = clock();
    for (int i = 0; i < 100000000; i++)
    {
        x = (double)rand() / RAND_MAX * (x_max - x_min) + x_min;
        z2 = my_pow(1.523);
    }
    end2 = clock();
    printf("%f my pow \n", (double)(end2 - start2) / CLOCKS_PER_SEC * 100000000);

    // compare values
    printf("%d \n", z1 == z2);
    printf("speedup: %f \n", (double)(end1 - start1) / (end2 - start2));

    return 0;
}

double my_pow(double x)
{
    // double result, x_squared;
    // result = x;
    // x_squared = x * x;
    // result *= x_squared;  // x^3
    // result *= result;     // x^6
    // result *= result;     // x^12
    // result *= result * x; // x^25
    // result *= result;     // x^50
    // result *= result;     // x^100
    //
    // return result;
    double x4, x32, xp;
    xp = x * x; // x^2
    xp *= xp;   // x^4
    x4 = xp;
    xp *= xp; // x^8
    xp *= xp; // x^16
    xp *= xp; // x^32
    x32 = xp;
    xp *= xp; // x^64

    return (x4 * x32 * xp); // x^(4+32+64)
}