
/*Write a C program to verify that the limit of 1 − 1/2^2 +1/2^4 −1/2^6 + . . . is 4/5 .*/
#include <stdio.h> // this is the most important thing to include in C
#include <math.h>  // this is to use the pow function
#include <stdlib.h>

void sort(int arr[], int beg, int end);

// make a function that takes in an array and returns a permutation vector
void perm_vec(int arr[], int p_vec[], int beg, int end);

void swap(int *a, int *b);

int main()
{
    int arr[] = {20, 10, 30};
    int arr2[] = {20, 10, 30};
    int *p_vec = malloc(3 * sizeof(int));
    // initialized it ordered
    for (int i = 0; i <= 2; i++)
    {
        p_vec[i] = i;
    }

    sort(arr, 0, 2);
    perm_vec(arr2, p_vec, 0, 2);
    for (int i = 0; i <= 2; i++)
    {
        printf("%i \n", arr[i]);
        printf("%i \n", arr2[p_vec[i]]);
    }
    // verify that arr2 has not been messed with
    for (int i = 0; i <= 2; i++)
    {
        printf("%i \n", arr2[i]);
    }
}

void swap(int *a, int *b)
{
    int temp = *a;
    *a = *b;
    *b = temp;
}

void sort(int arr[], int beg, int end)
{
    if (end > beg + 1)
    {
        int piv = arr[beg];
        int l = beg + 1;
        int r = end;
        while (l < r)
        {
            if (arr[l] <= piv)
                l++;
            else
                swap(&arr[l], &arr[--r]);
        }
        swap(&arr[--l], &arr[beg]);
        sort(arr, beg, l);
        sort(arr, r, end);
    }
}

void perm_vec(int arr[], int p_vec[], int beg, int end)
{
    if (end > beg + 1)
    {
        int piv = arr[p_vec[beg]];
        int l = beg + 1;
        int r = end;
        while (l < r)
        {
            if (arr[p_vec[l]] <= piv)
                l++;
            else
            {
                swap(&p_vec[l], &p_vec[--r]);
            }
        }
        swap(&p_vec[--l], &p_vec[beg]);
        perm_vec(arr, p_vec, beg, l);
        perm_vec(arr, p_vec, r, end);
    }
}