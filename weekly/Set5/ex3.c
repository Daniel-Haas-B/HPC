#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

void bad_foo(int N, double **mat, double **s, int *v);
void good_foo(int N, double **mat, double **s, int *v);
void supreme_foo(int N, double **mat, double **s, int *v, double *s2minuscos2_arr);

int main()
{
    int N = 2000;
    int M = 2000;

    double **mat1 = (double **)malloc(N * sizeof(double *));
    double **mat2 = (double **)malloc(N * sizeof(double *));
    double **mat3 = (double **)malloc(N * sizeof(double *));
    double **mat4 = (double **)malloc(N * sizeof(double *));

    double **s = (double **)malloc(N * sizeof(double *));

    int *v = (int *)malloc(N * sizeof(int));

    for (int i = 0; i < N; i++)
    {
        mat1[i] = (double *)malloc(M * sizeof(double));
        mat2[i] = (double *)malloc(M * sizeof(double));
        mat3[i] = (double *)malloc(M * sizeof(double));
        mat4[i] = (double *)malloc(M * sizeof(double));
        s[i] = (double *)malloc(M * sizeof(double));
    }

    // initialize mat and s and v
    for (int i = 0; i < N; i++)
    {
        for (int j = 0; j < M; j++)
        {
            s[i][j] = i - j;
        }
        v[i] = i;
    }
    clock_t start, end;

    int repeat = 100;
    start = clock();
    for (int i = 0; i < repeat; i++)
    {
        bad_foo(N, mat1, s, v);
    }
    end = clock();
    printf("Time taken by bad_foo: %f seconds\n", ((double)(end - start) / CLOCKS_PER_SEC) / repeat);

    start = clock();
    for (int i = 0; i < repeat; i++)
    {
        good_foo(N, mat2, s, v);
    }
    end = clock();
    printf("Time taken by good_foo: %f seconds\n", ((double)(end - start) / CLOCKS_PER_SEC) / repeat);

    start = clock();
    double *s2minuscos2_arr = (double *)malloc(N * sizeof(double));
    double val;
    for (int j = 0; j < N; j++)
    {
        val = 1.0 * (v[j] % 256);
        s2minuscos2_arr[j] = -cos(2 * val);
    }
    for (int i = 0; i < repeat; i++)
    {
        supreme_foo(N, mat3, s, v, s2minuscos2_arr);
    }
    free(s2minuscos2_arr);

    end = clock();
    printf("Time taken by supreme_foo: %f seconds\n", ((double)(end - start) / CLOCKS_PER_SEC) / repeat);

    //// print elements
    // for (int i = 0; i < N; i++)
    //{
    //     for (int j = 0; j < M; j++)
    //     {
    //         if (mat1[i][j] != mat2[i][j] || mat1[i][j] != mat3[i][j] || mat1[i][j] != mat4[i][j])
    //         {
    //             printf("mat1[%d][%d] = %f, mat2[%d][%d] = %f, mat3[%d][%d] = %f, mat4[%d][%d] = %f \n", i, j, mat1[i][j], i, j, mat2[i][j], i, j, mat3[i][j], i, j, mat4[i][j]);
    //         }
    //     }
    //     printf("\n");
    // }

    // free
    for (int i = 0; i < N; i++)
    {
        free(mat1[i]);
        free(mat2[i]);
        free(mat3[i]);
        free(s[i]);
    }
    free(mat1);
    free(mat2);
    free(mat3);
    free(s);
    free(v);

    return 0;
}

void bad_foo(int N, double **mat, double **s, int *v)
{
    int i, j;
    double val;
    for (j = 0; j < N; j++)
    {
        for (i = 0; i < N; i++)
        {
            val = 1.0 * (v[j] % 256);
            mat[i][j] = s[i][j] * (sin(val) * sin(val) - cos(val) * cos(val));
        }
    }
}

void good_foo(int N, double **mat, double **s, int *v)
{
    int i, j;
    double val;
    double s2minuscos2;
    for (j = 0; j < N; j++)
    {
        val = 1.0 * (v[j] % 256);
        s2minuscos2 = sin(val) * sin(val) - cos(val) * cos(val);
        for (i = 0; i < N; i++)
        {
            mat[i][j] = s[i][j] * s2minuscos2;
        }
    }
}

void supreme_foo(int N, double **mat, double **s, int *v, double *s2minuscos2_arr)
{
    int i, j;
    double val;

    for (j = 0; j < N; j++)
    {
        for (i = 0; i < N; i++)
        {
            mat[j][i] = s[j][i] * s2minuscos2_arr[i];
        }
    }
}
