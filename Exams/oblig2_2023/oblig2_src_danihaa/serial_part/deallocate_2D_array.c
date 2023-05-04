#include <stdlib.h>
#include <stdio.h>

void deallocate_2D_array(double **array)
{
  free(array[0]); // free the memory allocated for the array
  free(array);    // free the memory allocated for the pointers
}
