#include <stdlib.h>
#include <stdio.h>

void allocate_2D_array(double ***array_ptr, int nx, int ny)
{
  *array_ptr = (double **)malloc(ny * sizeof(double *)); // allocate memory for the array of pointers

  if (*array_ptr == NULL)
  {
    printf("Error: Could not allocate memory for the array of pointers.\n");
    exit(1);
  }

  (*array_ptr)[0] = (double *)malloc(nx * ny * sizeof(double)); // allocate memory for the array
  if ((*array_ptr)[0] == NULL)
  {
    printf("Error: Could not allocate memory for the array.\n");
    exit(1);
  }

  for (int i = 1; i < ny; i++)
  {
    (*array_ptr)[i] = (*array_ptr)[i - 1] + nx; // set the pointers to the correct locations
  }
}
