#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h> // to use the clock function

double f(double x);
double numerical_integration(double x_min, double x_max, int slices);

double x_min = 0;
double x_max = 1;
double result;
int slices = 10000000;

int main()
{
    // verification of convergence
    // for (int slice = 0; slice < slices; slice++)
    //{
    //    result = numerical_integration(x_min, x_max, slice);
    //    printf("diff from pi %f \n", result - M_PI);
    //}

    // actual implementation
    result = numerical_integration(x_min, x_max, slices);
    return 0;
}

double f(double x)
{
    double den = (1 + x * x); // we do this to isolate the division
    return 4 / den;
}

double numerical_integration(double x_min, double x_max, int slices)
{
    double delta_x = (x_max - x_min) / slices;
    double x, sum = 0.0;
    double den;
    double div_val;
    double cumul_t = 0.0;

    clock_t start, end;

    for (int i = 0; i < slices; i++)
    {
        x = x_min + (i + 0.5) * delta_x;
        den = (1 + x * x); // we do this to isolate the division
        start = clock();
        div_val = 4 / den;
        end = clock();
        cumul_t += ((double)(end - start));
        sum = sum + div_val;
    }
    printf("avg time for division %f \n", cumul_t / (CLOCKS_PER_SEC * slices));

    return sum * delta_x;
}

/*Notice that the number of divisions is the number of slices*/

// for (i = 0; i < N; i++)
//{
//     for (j = 0; j < N; j++)
//     {
//         C[i] += A[i][j] * B[j];
//     }
// }
//
// for (i = 0; i < N; i++)
//{
//     C[i] = tmp;
//     for (j = 0; j < N; j++)
//     {
//         tmp += A[i][j] * B[j];
//     }
//     C[i] = tmp;
// }