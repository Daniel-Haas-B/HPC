#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>   // to use the clock function
#include <string.h> // to use memcpy

int main()
{
    int n = 100000000;
    int stride = 8;
    double *A = (double *)malloc(n * sizeof(double)); // sizeof *A is the same as sizeof(double);
    double *B = (double *)malloc(n * sizeof(double));
    double s = 1.5;

    for (int i = 0; i < n; i++)
    {
        A[i] = (double)rand() / RAND_MAX;
        B[i] = (double)rand() / RAND_MAX;
    }
    clock_t start, end;
    start = clock();
    for (int i = 0; i < n; i += stride)
    {
        // here we see that we are transferring the data from B to A
        // assuming that all the time is spend on the transfer, we can measure the time it takes
        // to transfer 8 bytes of data.
        // after n iterations we have transferred n*8 bytes of data
        A[i] = s * B[i];
    }
    end = clock();
    double time_taken = (double)(end - start) / CLOCKS_PER_SEC;

    printf("memory bandwidth: %lf GB/s \n", (2 * n * sizeof(double)) / (time_taken * 1e9)); // i forgot to multiply by 2 because there is load and store
    printf("G Flops/sec  %lf \n", n / (stride * time_taken * 1e9));
    printf("time taken: %lf s", time_taken);

    free(A);
    free(B);

    return 0;
}
