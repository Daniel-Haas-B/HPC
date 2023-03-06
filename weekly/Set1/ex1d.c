/*Write a C program that allocates a 3D array of dimension (nx, ny, nz).
A 1D underlying contiguous storage should be used. Assign the values
of the 3D array, such as u[i][j][k]=i*n y*n z+j*n z+k. Deallocate
the 3D array at the end of the program.*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int n_x = 5;
int n_y = 5;
int n_z = 5;

void fill_cube(int ***cube, int n_x, int n_y, int n_z);

int main()
{
    // allocate a 3D array
    int ***cube = (int ***)malloc(n_x * sizeof(int **));

    for (int i = 0; i < n_x; i++)
    {
        cube[i] = (int **)malloc(n_y * sizeof(int *)); // cube[i] is a 2D array so we are allocating the memory for it
        for (int j = 0; j < n_y; j++)                  // now, inside this 2D array, we allocate the memory for the 1D array
        {
            cube[i][j] = (int *)malloc(n_z * sizeof(int)); // this is the underlaying 1D contiguous storage
        }
    }

    fill_cube(cube, n_x, n_y, n_z);

    printf("cube before free = %d \n", cube[2][2][2]);

    // free the memory. Notice that we free the memory in the opposite order
    for (int i = 0; i < n_x; i++)
    {
        for (int j = 0; j < n_y; j++)
        {
            free(cube[i][j]);
        }
        free(cube[i]);
    }
    free(cube); // this last free is needed because we allocated the memory for the 3D array
    printf("cube after free = %d \n", cube[2][2][2]);
    // what happens if we try to access the memory after we free it?
    // we CAN get a seg fault, but we can also get a the same number as before we free it
    // this is because the memory is not actually freed, it is just marked as free, to be used if needed

    return 0;
}

void fill_cube(int ***cube, int n_x, int n_y, int n_z)
{
    for (int i = 0; i < n_x; i++)
    {
        for (int j = 0; j < n_y; j++)
        {
            for (int k = 0; k < n_z; k++)
            {
                cube[i][j][k] = i * n_y * n_z + j * n_z + k;
            }
        }
    }
}
