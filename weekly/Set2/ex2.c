#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>   // to use the clock function
#include <string.h> // to use memcpy

int main()
{
    int n = 10000;
    clock_t start, end;

    double *A = (double *)malloc(n * sizeof(double));
    double *B = (double *)malloc(n * sizeof(double));
    double *C = (double *)malloc(n * sizeof(double));

    // fill A while leaving B empty
    for (int i = 0; i < n; i++)
    {
        A[i] = i;
    }
    start = clock();
    // need to do it multiple times to get a good time
    for (int i = 0; i < 100000; i++)
    {
        for (int j = 0; j < n; j++)
        {
            B[j] = A[j];
        }
    }
    end = clock();
    printf("Time to HAND copy array %f \n", (((double)(end - start)) / CLOCKS_PER_SEC) / 100000);

    // now copy A to C using memcpy
    start = clock();
    // need to do it multiple times to get a good time
    for (int i = 0; i < 100000; i++)
    {
        memcpy(C, A, n * sizeof(double));
    }
    end = clock();
    printf("Time to memcpy array %f \n", (((double)(end - start)) / CLOCKS_PER_SEC) / 100000);
    return 0;
}
