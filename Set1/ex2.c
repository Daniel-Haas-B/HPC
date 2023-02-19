/*Write a C program that reads from a data file containing one day’s
temperature measurements of the following format:*/

#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

double avg_temp(double *temp_arr, int n_lines); // we get the pointer if we want to modify the array.

double std_temp(double *temp_arr, int n_lines);

void create_data(int n_lines, float timestep);

void read_data(char *filename, int n_lines, double *temp_arr, char *hour_arr);

struct data
{
    double temp;
    char hour[5];
};

// struct data find_min(double *temp_arr, *hour_arr, int n_lines);
struct data find_max(double *temp_arr, char *hour_arr, int n_lines);

int main()
{
    int n_lines = 100;    // 100 temperature measurements
    float timestep = 0.1; // 6 min measurements

    create_data(n_lines, timestep);
    printf("Data written to file temperature_data.txt");

    double *temp_arr = malloc(n_lines * sizeof(double));
    char *hour_arr = malloc(n_lines * sizeof(double));

    read_data("temperature_data.txt", n_lines, temp_arr, hour_arr);

    struct data data_max = find_max(temp_arr, hour_arr, n_lines);
    printf("max temp %f max data %s", data_max.temp, data_max.hour);

    return 0;
}

void create_data(int n_lines, float timestep)
{
    int hour;
    double time;
    int minutes;
    double *temp_arr = malloc(n_lines * sizeof(double));
    double *time_arr = malloc(n_lines * sizeof(double));

    FILE *fp;                                // We want to write to a file and not to the terminal. The pointer is a variable that points to the file.
    fp = fopen("temperature_data.txt", "w"); // w means write. If the file does not exist, it will be created.

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

void read_data(char *filename, int n_lines, double *temp_arr, char *hour_arr)
{
    FILE *fp;
    fp = fopen(filename, "r"); // r means read. If the file does not exist, it will be created.

    char hour[5];
    double temp;
    int i = 0;
    while (fscanf(fp, "%s %lf", hour, &temp) != EOF)
    {
        temp_arr[i] = temp;
        strcpy(&hour_arr[i], hour);
        i++;
    }
    // print type of data
    fclose(fp);
}

struct data find_max(double *temp_arr, char *hour_arr, int n_lines)
{
    double temp_max = temp_arr[0];
    char hour_max[5];

    for (int i = 0; i < n_lines; i++)
    {
        if (temp_arr[i] > temp_max)
        {
            temp_max = temp_arr[i];
            strcpy(hour_max, &hour_arr[i]);
        }
    }
    struct data data_max;

    strcpy(hour_max, data_max.hour);
    data_max.temp = temp_max;
    return data_max;
}
