/*When assigning values to the entries of a m × n matrix, it is common
to use a nested for-loop with the outer index looping over the rows
and the inner index looping over the columns. Does it matter if the
sequence of these two loops is swapped? Write a C program to test
your hypothesis.*/

/*I think it matter because C saves arrays in a row major way*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h> // to use the clock function

// pass the memory address of the matrix
int m = 5000;
int n = 5000;

void fill_matrix_A(int **matrix, int m, int n);
void fill_matrix_B(int **matrix, int m, int n);

int main()
{
    int **matrix_A = (int **)malloc(m * sizeof(int *));
    int **matrix_B = (int **)malloc(m * sizeof(int *));

    for (int i = 0; i < m; i++)
    {
        matrix_A[i] = (int *)malloc(n * sizeof(int));
        matrix_B[i] = (int *)malloc(n * sizeof(int));
    }

    double time_A, time_B;
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    for (int i = 0; i < 100; i++)
    {
        fill_matrix_A(matrix_A, m, n);
    }
    end = clock();
    time_A = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    for (int i = 0; i < 100; i++)
    {
        fill_matrix_B(matrix_B, m, n);
    }
    end = clock();
    time_B = ((double)(end - start)) / CLOCKS_PER_SEC;

    // print element matrix_A[2][7] and matrix_B[2][7]
    printf("matrix_A[2][7] = %d \n", matrix_A[2][7]);
    printf("matrix_B[2][7] = %d \n", matrix_B[2][7]);

    printf("AVG Time to fill A %f \n", time_A / 100);
    printf("AVG Time to fill B %f \n", time_B / 100);

    return 0;
}

void fill_matrix_A(int **matrix, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = i;
        }
    }
}

void fill_matrix_B(int **matrix, int m, int n)
{
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < m; i++)
        {
            matrix[i][j] = i;
        }
    }
}

/* this exercise is very intereting because it can be done in a way that you dont measure any difference.
if, for example, we define the matrices as int matrix_A[m][n]; and int matrix_B[m][n]; and the function as
void fill_matrix_A(int matrix[m][n], int m, int n); and void fill_matrix_B(int matrix[m][n], int m, int n);
then the compiler will optimize the memory elements are actually taken from the stack and not from the heap.
so the compiler will optimize the code and the time will be the same, I think.

Here is the previous code with the changes I mentioned above:

but the following code does not show this, why? code: #include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h> // to use the clock function

// pass the memory address of the matrix
int m = 1000;
int n = 1000;

void fill_matrix_A(int (*matrix)[n], int m, int n);
void fill_matrix_B(int (*matrix)[n], int m, int n);

int main()
{
    int matrix_A[m][n];
    int matrix_B[m][n];

    double time_A, time_B;
    clock_t start, end;
    double cpu_time_used;

    start = clock();
    for (int i = 0; i < 100; i++)
    {
        fill_matrix_A(matrix_A, m, n);
    }
    end = clock();
    time_A = ((double)(end - start)) / CLOCKS_PER_SEC;

    start = clock();
    for (int i = 0; i < 100; i++)
    {
        fill_matrix_B(matrix_B, m, n);
    }
    end = clock();
    time_B = ((double)(end - start)) / CLOCKS_PER_SEC;

    // print element matrix_A[2][7] and matrix_B[2][7]
    printf("matrix_A[2][7] = %d \n", matrix_A[2][7]);
    printf("matrix_B[2][7] = %d \n", matrix_B[2][7]);

    printf("AVG Time to fill A %f \n", time_A / 100);
    printf("AVG Time to fill B %f \n", time_B / 100);

    return 0;
}

void fill_matrix_A(int (*matrix)[n], int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            matrix[i][j] = 1;
        }
    }
}

void fill_matrix_B(int (*matrix)[n], int m, int n)
{
    for (int j = 0; j < n; j++)
    {
        for (int i = 0; i < m; i++)
        {
            matrix[i][j] = 1;
        }
    }
}
*/
