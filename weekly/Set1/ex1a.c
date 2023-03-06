
/*Write a C program to verify that the limit of 1 − 1/2^2 +1/2^4 −1/2^6 + . . . is 4/5 .*/
#include <stdio.h> // this is the most important thing to include in C
#include <math.h>  // this is to use the pow function

// global variables
double val = 1;
double diff = 0;
double lim = 0.8; // 4/5
double eps = 1e-10;
int sign = 1;
int i = 2;

int main()
{

    do
    {
        sign *= -1; // this can be faster than using the pow function
        val += (1.0 / pow(2., i)) * sign;
        i += 2;
        diff = fabs(val - lim);

    } while (diff > eps);                            // notice this is just like C++ but not like Python also, this could`ve been a simple while loop.
    printf("The value of the series is %f \n", val); // this is how you print in C versus std::cout in C++
    printf("The difference between the series and the limit is %f \n", diff);
    printf("The expected limit is %f", lim);

    return 0;
}