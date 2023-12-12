#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include "functions.h"

 // gcc newton.c functions.c -Wall -o main.exe
 // ./main.exe
int main() {
    double const tolerance = 1e-10;
    int const maxIterations = 1000;
    double x = 1.0;
    int operation;

    
    printf("---------------------------------------------------------------------------------\n");
    printf("This program calculates the root of a function with the newton raphson algorythm.\n");
    printf("---------------------------------------------------------------------------------\n\n");

    printf("enter the start x value.\n");
    printf("answer: ");
    scanf("%lf", &x);

    printf("\nwhich operation you want to use?.\n");
    printf("1: analytic derivation\n");
    printf("2: numeric derivation\n");
    printf("answer: ");
    scanf("%i", &operation);

    if(operation != 1 && operation != 2)
    {
        printf("ERROR: no valid operation.");
        return EXIT_FAILURE;
    }

    double (*f_ptr)(double) = &f;
    double (*df_ptr)(double) = &df;
    double (*df_approx_ptr)(double) = &df_approx;

    for (int i = 0; i < maxIterations; i++)
    {
        double h;

        if(operation == 1){
            h = (*f_ptr)(x) / (*df_ptr)(x);
        }else if (operation == 2){
            h = (*f_ptr)(x) / (*df_approx_ptr)(x);
        }

        // x(i+1) = x(i) - f(x) / f'(x)
        x = x - h;

        if (fabs(h) < tolerance)
        {
            printf("\nroot found at x = %f\n", x);
            printf("needed iterations = %i\n", i);
            return EXIT_SUCCESS;
        }

        if(i == maxIterations -1)
        {
            printf("WARNING: root couldn't be found within the max iteration range.");
            return EXIT_FAILURE;
        }
    }

    printf("ERROR: root couldn't be found.");
    return EXIT_FAILURE;
}

