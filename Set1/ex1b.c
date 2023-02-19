
/*Write a C program that allocates a 1D array of length n which is
prescribed at runtime. You are supposed to first assign the values
of the array with random numbers, and then find the maximum and
minimum values. (You can use e.g. the rand function from stdlib.h.)*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>

int n;

struct min_max
{
    double max_val;
    double min_val;
};

struct min_max find_min_max(double *arr);

int main()
{

    printf("Enter number of elements: ");
    scanf("%d", &n);

    // initialize the array with random numbers and print it
    double *arr = malloc(n * sizeof(double));
    for (int i = 0; i < n; i++)
    {
        arr[i] = rand() % 100;
        printf("%f \n", arr[i]);
    }

    struct min_max min_max = find_min_max(arr);

    printf("The max value of the array is %f \n", min_max.max_val);
    printf("The min value of the array is %f \n", min_max.min_val);

    return 0;
}

struct min_max find_min_max(double *arr)
{
    double max_val = arr[0];
    double min_val = arr[0];
    for (int i = 0; i < n; i++)
    {
        if (arr[i] > max_val)
        {
            max_val = arr[i];
        }
        if (arr[i] < min_val)
        {
            min_val = arr[i];
        }
    }
    struct min_max min_max;
    min_max.max_val = max_val;
    min_max.min_val = min_val;
    return min_max;
}
