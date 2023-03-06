#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>   // to use the clock function
#include <string.h> // to use memcpy

void mat_mul(double **A, double **B, double **C);
void mat_mul_unroll(double **A, double **B, double **C);

int n = 4;
int m = 4;
int p = 4;

int main()
{
    // alocate memory
    double **A = (double **)malloc(n * sizeof(double *));
    double **B = (double **)malloc(m * sizeof(double *));
    double **C = (double **)malloc(n * sizeof(double *));
    double **D = (double **)malloc(n * sizeof(double *));

    for (int i = 0; i < n; i++)
    {
        A[i] = (double *)malloc(m * sizeof(double));
        C[i] = (double *)malloc(p * sizeof(double));
        D[i] = (double *)malloc(p * sizeof(double));
    }
    for (int i = 0; i < m; i++)
    {
        B[i] = (double *)malloc(p * sizeof(double));
    }

    // fill matrices A and B
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            // random number between 0 and 1
            A[i][j] = (double)rand() / RAND_MAX;
        }
    }
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < p; j++)
        {
            // random number between 0 and 1
            B[i][j] = (double)rand() / RAND_MAX;
        }
    }
    // multiply them
    clock_t start, end;

    start = clock();
    mat_mul(A, B, C);
    end = clock();
    printf("Time for the dumb mat mult %lf \n", (double)(end - start) / CLOCKS_PER_SEC);
    start = clock();
    mat_mul_unroll(A, B, D);

    end = clock();
    printf("Time for the UNROLLED mat mult %lf \n", (double)(end - start) / CLOCKS_PER_SEC);

    // verify that they are the same results
    printf("Are they the same results? %d \n", D == C);

    for (int i = 0; i < n; i++)
    {
        free(A[i]);
        free(C[i]);
    }
    for (int i = 0; i < m; i++)
    {
        free(B[i]);
    }
    free(A);
    free(B);
    free(C);

    return 0;
}

void mat_mul(double **A, double **B, double **C)
{
    double temp;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < p; j++)
        {
            temp = 0;
            for (int k = 0; k < m; k++)
            {
                temp += A[i][k] * B[k][j];
            }
            C[i][j] = temp;
        }
    }
};

void mat_mul_unroll(double **A, double **B, double **C)
{
    int rest = p % 3;
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < p - rest; j += 3) // if we unroll B[k][j] in j, we need a stride here!!!
        {
            for (int k = 0; k < m; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
                C[i][j + 1] += A[i][k] * B[k][j + 1];
                C[i][j + 2] += A[i][k] * B[k][j + 2];
            }
        }
        // additional code in case p is not divisible by the stride
        for (int j = p - rest; j < p; j++)
        {
            for (int k = 0; k < m; k++)
            {
                C[i][j] += A[i][k] * B[k][j];
            }
        }
    }
};
