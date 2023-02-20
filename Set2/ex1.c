#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h> // to use the clock function

void write_ascii_file(char *filename, double **data, int m, int n);
void read_ascii_file(char *filename, double **data, int m, int n);

void write_binary_file(char *filename, double **data, int m, int n);
void read_binary_file(char *filename, double **data, int m, int n);

void create_data(double **M, int m, int n);

int main()
{
    int m = 500;
    int n = 500;
    clock_t start, end;

    double **M = (double **)malloc(m * sizeof(double));
    for (int i = 0; i < m; i++)
    {
        M[i] = (double *)malloc(n * sizeof(double)); // allocate the memory for the columns
    }

    double **M_read_ascii = (double **)malloc(m * sizeof(double));
    for (int i = 0; i < m; i++)
    {
        M_read_ascii[i] = (double *)malloc(n * sizeof(double)); // allocate the memory for the columns
    }

    double **M_read_binary = (double **)malloc(m * sizeof(double));
    for (int i = 0; i < m; i++)
    {
        M_read_binary[i] = (double *)malloc(n * sizeof(double)); // allocate the memory for the columns
    }

    create_data(M, m, n);

    // time to write ascii file
    start = clock();
    write_ascii_file("ascii_test.txt", M, m, n);
    end = clock();
    printf("Time to write ascii file %f \n", ((double)(end - start)) / CLOCKS_PER_SEC);

    // time to write binary file
    start = clock();
    write_binary_file("binary_test.bin", M, m, n);
    end = clock();
    printf("Time to write binary file %f \n", ((double)(end - start)) / CLOCKS_PER_SEC);

    // time to read ascii file
    start = clock();
    read_ascii_file("ascii_test.txt", M_read_ascii, m, n);
    end = clock();
    printf("Time to read ascii file %f \n", ((double)(end - start)) / CLOCKS_PER_SEC);

    // time to read binary file
    start = clock();
    read_binary_file("binary_test.bin", M_read_binary, m, n);
    end = clock();
    printf("Time to read binary file %f \n", ((double)(end - start)) / CLOCKS_PER_SEC);

    // check if the data is the same
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (M[i][j] != M_read_ascii[i][j] || M[i][j] != M_read_binary[i][j])
            {
                printf("Error in reading file \n");
                printf("M[%d][%d] = %f \n", i, j, M[i][j]);
                printf("M_read_ascii[%d][%d] = %f \n", i, j, M_read_ascii[i][j]);
                printf("M_read_binary[%d][%d] = %f \n", i, j, M_read_binary[i][j]);
                exit(1);
            }
        }
    }

    return 0;
}

void write_ascii_file(char *filename, double **data, int m, int n)
{
    FILE *fp;
    fp = fopen(filename, "w");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (j == n - 1)
            {
                fprintf(fp, "%f \n", data[i][j]);
            }
            else
            {
                fprintf(fp, "%f ", data[i][j]);
            }
        }
    }
    fclose(fp);
}

void write_binary_file(char *filename, double **data, int m, int n)
{
    FILE *fp;
    fp = fopen(filename, "wb"); // open the file in binary mode
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fwrite(&data[i][j], sizeof(double), 1, fp); // fwrite is used to write binary data the
        }
    }
    fclose(fp);
}

void create_data(double **M, int m, int n)
{
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            M[i][j] = (i + j) % 10;
        }
    }
}

void read_ascii_file(char *filename, double **data, int m, int n)
{
    FILE *fp;
    fp = fopen(filename, "r");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fscanf(fp, "%lf", &data[i][j]);
        }
    }
    fclose(fp);
}

void read_binary_file(char *filename, double **data, int m, int n)
{
    FILE *fp;
    fp = fopen(filename, "rb");
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            fread(&data[i][j], sizeof(double), 1, fp);
        }
    }
    fclose(fp);
}
