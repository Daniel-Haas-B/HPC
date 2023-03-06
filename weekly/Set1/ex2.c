/*Write a C program that reads from a data file containing one day’s
temperature measurements of the following format:*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

double avg_temp(double *temp_arr, int n_lines); // we get the pointer if we want to modify the array.

double std_temp(double *temp_arr, double avg, int n_lines);

void create_data(char *filename, int n_lines, float timestep);

void read_data(char *filename, int n_lines, double *temp_arr, char *hour_arr);

void fill_V(double **V, int m, int n);

void smooth(double **V, int n, int m, double c);

struct data
{
    double temp;
    char hour;
};

// struct data find_min(double *temp_arr, *hour_arr, int n_lines);
struct data find_max(double *temp_arr, char *hour_arr, int n_lines);

int main()
{
    int n_lines = 100;    // 100 temperature measurements
    float timestep = 0.1; // 6 min measurements

    create_data("temperature_data.txt", n_lines, timestep);
    printf("Data written to file temperature_data.txt \n");

    double *temp_arr = malloc(n_lines * sizeof(double));
    char *hour_arr = malloc(n_lines * sizeof(char));

    read_data("temperature_data.txt", n_lines, temp_arr, hour_arr);

    struct data data_max = find_max(temp_arr, hour_arr, n_lines);
    printf("max temp %f max data %c \n", data_max.temp, data_max.hour);
    double avg = avg_temp(temp_arr, n_lines);
    printf("avg temp %f \n", avg);
    double std = std_temp(temp_arr, avg, n_lines);
    printf("std temp %f", std);

    // allocate the 2d array to smooth
    int m = 5;
    int n = 5;
    double **V = (double **)malloc(m * sizeof(double));
    for (int i = 0; i < m; i++)
    {
        V[i] = (double *)malloc(n * sizeof(double));
    }

    // fill it with random stuff
    fill_V(V, m, n);
    // print before smooth
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%f ", V[i][j]);
        }
        printf("\n");
    }
    printf("smoothing \n");
    smooth(V, n, m, 0.5);
    // print after smooth
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            printf("%f ", V[i][j]);
        }
        printf("\n");
    }

    return 0;
}

void create_data(char *filename, int n_lines, float timestep)
{
    int hour;
    double time;
    int minutes;
    double *temp_arr = malloc(n_lines * sizeof(double));
    double *time_arr = malloc(n_lines * sizeof(double));

    FILE *fp;                  // We want to write to a file and not to the terminal. The pointer is a variable that points to the file.
    fp = fopen(filename, "w"); // w means write. If the file does not exist, it will be created.

    for (int i = 0; i < n_lines; i++)
    {
        temp_arr[i] = 20 + 5 * sin(2 * M_PI * i * timestep);
        time = i * timestep;
        hour = time / 1;
        minutes = (time - hour) * 60;
        time_arr[i] = hour + minutes / 60.0; // this is not necessary, but it is good to have the time in hours.
        // You need to use %02d if you want leading zeroes padded to two spaces and the %f is a placeholder for a float.
        fprintf(fp, "%02d:%02d %f\n", hour, minutes, temp_arr[i]); // fprintf is used to write to a file.
    }
    fclose(fp); // We need to close the file when we are done with it.
}

double avg_temp(double *temp_arr, int n_lines)
{
    double sum = 0;
    for (int i = 0; i < n_lines; i++)
    {
        sum += temp_arr[i];
    }
    return sum / n_lines;
}

double std_temp(double *temp_arr, double avg, int n_lines)
{
    double sum = 0;

    for (int i = 0; i < n_lines; i++)
    {
        sum += pow((temp_arr[i] - avg), 2);
    }
    return sqrt(sum / (n_lines - 1));
}

void read_data(char *filename, int n_lines, double *temp_arr, char *hour_arr)
{
    FILE *fp;
    printf("Reading data from file %s \n", filename);
    fp = fopen(filename, "r"); // r means read. If the file does not exist, it will be created.
    char linechar;
    if (NULL == fp)
    {
        printf("file can't be opened \n");
    }

    for (int i = 1; i < n_lines; i++)
    {
        fscanf(fp, "%5s %lf", &hour_arr[5 * i], &temp_arr[i]);
    }

    fclose(fp);
}

struct data find_max(double *temp_arr, char *hour_arr, int n_lines)
{
    double temp_max = temp_arr[1];
    // print temp_max and type
    char hour_max;

    for (int i = 1; i < n_lines + 1; i++) // we start from 1 because the first line is weird
    {
        if (temp_arr[i] > temp_max)
        {
            temp_max = temp_arr[i];
            hour_max = hour_arr[i];
        }
    }
    // printf("max temp %f", temp_max);
    // printf("max hour %c", hour_max);
    struct data data_max;

    // strcpy(hour_max, data_max.hour);
    data_max.temp = temp_max;
    data_max.hour = hour_max;
    return data_max;
}

void smooth(double **V, int n, int m, double c)
{
    for (int i = 0; i < n; i++)
    {
        for (int j; j < m; j++)
        {
            V[i][j] = V[i][j] + c * (V[i - 1][j] + V[i][j - 1] - 4 * V[i][j] + V[i][j + 1] + V[i + 1][j]);
        }
    }
}

void fill_V(double **V, int m, int n)
{
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
        {
            V[i][j] = rand() % 100;
        }
    }
}