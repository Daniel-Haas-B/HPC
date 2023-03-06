#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void unroll_and_jam(double **A, double *B, double *y, int N);
void normal_mult(double **A, double *B, double *y, int N);

int main()
{
    int N = 1000;
    int M = 1000;

    double **A = (double **)malloc(N * sizeof(double *));
    double *B = (double *)malloc(N * sizeof(double));
    double *y1 = (double *)malloc(N * sizeof(double));
    double *y2 = (double *)malloc(N * sizeof(double));

    for (int i = 0; i < N; i++)
    {
        A[i] = (double *)malloc(M * sizeof(double));
    }

    // initialize A and B
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            A[i][j] = i + j;
        }
        B[i] = i;
    }
    clock_t start, end;

    int repeat = 10000;
    start = clock();
    for (int i = 0; i < repeat; i++)
    {
        unroll_and_jam(A, B, y1, N);
    }
    end = clock();
    printf("Time taken by unroll_and_jam: %f seconds\n", ((double)(end - start) / CLOCKS_PER_SEC) / repeat);

    start = clock();
    for (int i = 0; i < repeat; i++)
    {
        normal_mult(A, B, y2, N);
    }
    end = clock();
    printf("Time taken by normal_mult: %f seconds\n", ((double)(end - start) / CLOCKS_PER_SEC) / repeat);

    // free
    for (int i = 0; i < N; i++)
    {
        free(A[i]);
    }
    free(A);
    free(B);
    free(y1);
    free(y2);

    return 0;
}

void normal_mult(double **A, double *B, double *y, int N)
{
    // N = size of A[0]
    for (int j = 0; j < N; j++)
    {
        for (int i = 0; i <= j; i++)
        {
            y[j] += A[j][i] * B[i];
        }
    }
}

void unroll_and_jam(double **A, double *B, double *y, int N)
{
    // N = size of A[0]

    for (int j = 0; j < N - (N % 4); j += 4)
    {
        for (int i = 0; i <= j; i++)
        {
            y[j] += A[j][i] * B[i];
            y[j + 1] += A[j + 1][i] * B[i];
            y[j + 2] += A[j + 2][i] * B[i];
            y[j + 3] += A[j + 3][i] * B[i];
        }
        // given the i < j condition, some values of y are not calculated
        // Notice the values of i:
        // 0
        // 0 1 2 3 4
        // 0 1 2 3 4 5 6 7 8
        // 0 1 2 3 4 5 6 7 8 9 10 11 12
        // ...
        // But they should be:
        // 0
        // 0 1
        // 0 1 2
        // 0 1 2 3
        // 0 1 2 3 4
        // 0 1 2 3 4 5
        // ...
        y[j + 1] += A[j + 1][j + 1] * B[j + 1];
        y[j + 2] += A[j + 2][j + 1] * B[j + 1];
        y[j + 2] += A[j + 2][j + 2] * B[j + 2];
        y[j + 3] += A[j + 3][j + 1] * B[j + 1];
        y[j + 3] += A[j + 3][j + 2] * B[j + 2];
        y[j + 3] += A[j + 3][j + 3] * B[j + 3];
    }

    // Rest loop.
    for (int j = N - (N % 4); j < N; j++)
    {
        for (int i = 0; i <= j; i++)
        {
            y[j] += A[j][i] * B[i];
        }
    }
}
