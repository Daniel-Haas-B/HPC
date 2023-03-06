

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

int n_x = 5;
int n_y = 5;
int n_z = 5;

void fill_cube_V(double ***V, int n_x, int n_y, int n_z);
void fill_cube_U(double ***U, double ***V, int n_x, int n_y, int n_z);

int main()
{
    // allocate a 3D array
    double ***cube_V = (double ***)malloc(n_x * sizeof(double **));
    double ***cube_U = (double ***)calloc(n_x, sizeof(double **)); // calloc is used to initialize the memory to 0 notice the different sintax

    for (int i = 0; i < n_x; i++)
    {
        cube_V[i] = (double **)malloc(n_y * sizeof(double *)); // cube[i] is a 2D array so we are allocating the memory for it
        cube_U[i] = (double **)calloc(n_y, sizeof(double *));  // calloc is used to initialize the memory to 0 notice the different sintax
        for (int j = 0; j < n_y; j++)                          // now, inside this 2D array, we allocate the memory for the 1D array
        {
            cube_V[i][j] = (double *)malloc(n_z * sizeof(double)); // this is the underlaying 1D contiguous storage
            cube_U[i][j] = (double *)calloc(n_z, sizeof(double));  // this is the underlaying 1D contiguous storage
        }
    }
    printf("Memory allocated\n");
    // check if U is initialized to 0

    fill_cube_V(cube_V, n_x, n_y, n_z);
    printf("V filled\n");

    fill_cube_U(cube_U, cube_V, n_x, n_y, n_z);

    printf("U filled\n");
    // free the memory
    for (int i = 0; i < n_x; i++)
    {
        for (int j = 0; j < n_y; j++)
        {
            free(cube_V[i][j]);
            free(cube_U[i][j]);
        }
        free(cube_V[i]);
        free(cube_U[i]);
    }
    free(cube_V);
    free(cube_U);
    printf("Memory freed\n");

    return 0;
}

void fill_cube_V(double ***V, int n_x, int n_y, int n_z)
{
    int den = (n_x - 1) * (n_y - 1) * (n_z - 1);
    for (int i = 0; i < n_x; i++)
    {
        for (int j = 0; j < n_y; j++)
        {
            for (int k = 0; k < n_z; k++)
            {
                V[i][j][k] = 2 + sin(i * j * k * M_PI / den);
            }
        }
    }
}

void fill_cube_U(double ***U, double ***V, int n_x, int n_y, int n_z)
{
    for (int i = 1; i < n_x - 2; i++)
    {
        for (int j = 1; j < n_y - 2; j++)
        {
            for (int k = 1; k < n_z - 2; k++)
            {
                U[i][j][k] = V[i][j][k] + (V[i - 1][j][k] + V[i][j - 1][k] + V[i][j][k - 1] - 6 * V[i][j][k] + V[i + 1][j][k] + V[i][j + 1][k] + V[i][j][k + 1]) / 6;
                // now copy the content of U to V with memcpy
                memcpy(V[i][j], U[i][j], n_z * sizeof(double));
            }
        }
    }
}

// I think this is wrong
// flops_fill_cube_U = 7 * (n_x-2) * (n_y-2) * (n_z-2)   // number of additions
//    + 6 * (n_x-2) * (n_y-2) * (n_z-2)   // number of subtractions
//    + (n_x-2) * (n_y-2) * (n_z-2)       // number of multiplications
//    + (n_x-2) * (n_y-2) * (n_z-2)       // number of divisions
