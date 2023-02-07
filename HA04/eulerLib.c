#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "eulerLib.h"

#define NUMOFSTATES 2
#define SIMDATAFILE "simData.txt"

void rhsMSD(double *rhs, double *y)
{ // mass spring damper

    double m = 1.0;  // mass of object
    double c = 5;    // feder constant
    double d = 0.25; // damper constant

    double x = y[0]; // position
    double v = y[1]; // speed

    /*calc derivatives and store in rhs*/
    rhs[0] = -(d/m * v + c/m * x);
    rhs[1] = v;
}

void eulerSettingsMSD(simHandle *handle)
{

    /*num of states*/
    handle->numOfStates = NUMOFSTATES;

    /*right hand site*/
    handle->f = rhsMSD;

    /*reserve storage for init state vec*/
    handle->stateVecInit = (double *)malloc(sizeof(double) * (handle->numOfStates));
    if(handle->stateVecInit == NULL){
        printf("ERROR: can't allocate space.\n");
        return;
    }

    /*get user defined Simtime*/
    printf("Simtime (in s): \n");
    scanf("%lf", &(handle->simTime));

    /*get user defined StepSize*/
    printf("StepSize (in s): \n");
    scanf("%lf", &(handle->stepSize));

    /*get init state position*/
    printf("position(t = 0): \n");
    scanf("%lf", &(handle->stateVecInit[0]));
    // mit 1 anfangen

    /*get init state speed*/
    printf("speed(t = 0): \n");
    scanf("%lf", &(handle->stateVecInit[1]));
    // mit 0 anfangen

    /*reserve storage for states and derivatives*/
    int integratorSteps = (int)ceil(handle->simTime / handle->stepSize);
    handle->stateVec = (double *)malloc(handle->numOfStates * integratorSteps * sizeof(double));
    if(handle->stateVec == NULL){
        printf("ERROR: can't allocate space.\n");
        return;
    }

    /*init states and derivatives with zero*/
    handle->derivStateVec = (double *)malloc(sizeof(handle->stateVec) * sizeof(double));
    if(handle->derivStateVec == NULL){
        printf("ERROR: can't allocate space.\n");
        return;
    }
}

void eulerForward(simHandle *handle)
{ // this is called only once
    int numOfStates = handle->numOfStates;
    int integratorSteps = (int)ceil(handle->simTime / handle->stepSize);
    printf("\nsteps: %i\n", integratorSteps);

    /*write init states*/
    for (int i = 0; i < numOfStates; i++)
    {
        handle->stateVec[i] = handle->stateVec[i];
    }
    for (int i = 0; i < integratorSteps; i++)
    {
        /*get derivatives*/
        //handle->f(handle->derivStateVec, handle->stateVec);
        
        handle->stateVec[i + i] = handle->stateVec[i] + handle->derivStateVec[i] * handle->stepSize;
        handle->derivStateVec[i + i] = handle->derivStateVec[i] + handle->derivStateVec[i] * handle->stepSize;

        for (int j = 0; j < numOfStates; j++)
        {
            /*euler step*/
            handle->stateVec[i + i + j] = handle->stateVec[i-1] + handle->derivStateVec[i] * handle->stepSize;
            handle->derivStateVec[i + i + j] = handle->stateVec[i-1] + handle->derivStateVec[i] * handle->stepSize;
        }
    }
}

void showResultsMSD(simHandle *handle)
{

    /*print data to text file*/
    FILE *fh;
    int integratorSteps = (int)ceil(handle->simTime / handle->stepSize);

    fh = fopen(SIMDATAFILE, "w");
    if(fh == NULL)
    {
        printf("ERROR: file %s couldnt be opened.", SIMDATAFILE);
    }
    else
    {
        for (int i = 0; i < integratorSteps; i++)
        {
            // i * handle->stepSize,
            fprintf(fh, "%lf %lf %lf %lf\n", handle->stateVec[i+i], handle->stateVec[i+i+1], handle->derivStateVec[i+i],handle->derivStateVec[i+i+1]);
        }

        fclose(fh);
    }

    /*call gnuplot*/
    generatePlot();
}

void generatePlot()
{
    FILE *gnuplotPipe;

    gnuplotPipe = popen("gnuplot -persistent", "w");

    if(gnuplotPipe == NULL)
    {
        printf("ERROR: stream couldnt be opened.");
    }
    else
    {
        //fprintf(gnuplotPipe, "set xlabel 'time'\n");
        fprintf(gnuplotPipe, "plot "
        "'%s' using 1:2 title 'position', "
        "'%s' using 3:4 title 'speed'\n", 
        SIMDATAFILE, SIMDATAFILE);

        fprintf(gnuplotPipe, "exit");
        pclose(gnuplotPipe);
    }
}
