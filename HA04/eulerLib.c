#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "eulerLib.h"

#define NUMOFSTATES 2

void rhsMSD(double *rhs, double *y)
{ // mass spring damper

    double m = 1.0;  // mass of object
    double c = 2.0;  // feder constant
    double d = 3.0;  // damper constant

    double x = y[0]; // position
    double v = y[1]; // speed

    /*calc derivatives and store in rhs*/
    rhs[0] = v;
    rhs[1] = -((d*v/m)+(c*x/m));
}

void eulerSettingsMSD(simHandle *handle)
{
    int integratorSteps = 0;

    /*num of states*/
    handle->numOfStates = (int)NUMOFSTATES;

    /*right hand site*/
    handle->f = &rhsMSD;

    /*reserve storage for init state vec*/
    handle->stateVecInit = malloc(sizeof(double) * (handle->numOfStates));
    if(handle->stateVecInit == NULL){
        printf("ERROR: can't allocate space.\n");
        return;
    }

    /*get user defined Simtime*/
    printf("Simtime (in s): \n");
    scanf("%lf", &(handle->simTime));
    if(handle->simTime < 0){
        printf("ERROR: invalid input for simtime, simtime must not be negative or zero\n");
        return;
    }

    /*get user defined StepSize*/
    printf("StepSize (in s): \n");
    scanf("%lf", &(handle->stepSize));
    if (handle->stepSize < 0){
        printf("ERROR: invalid input for stepsize, stepsize must not be negative or zero\n");
        return;
    }

    /*get init state position*/
    printf("position(t = 0): \n");
    scanf("%lf", &(handle->stateVecInit[0]));
    
    /*get init state speed*/
    printf("speed(t = 0): \n");
    scanf("%lf", &(handle->stateVecInit[1]));

    /*reserve storage for states and derivatives*/
    integratorSteps = (int)ceil(handle->simTime / handle->stepSize);
    handle->stateVec = malloc(sizeof(double) * (handle->numOfStates) * integratorSteps);
    if(handle->stateVec == NULL){
        printf("ERROR: can't allocate space.\n");
        return;
    }

    handle->derivStateVec = malloc(sizeof(double) *(handle->numOfStates) * integratorSteps);
    if(handle->derivStateVec == NULL){
        printf("ERROR: can't allocate space.\n");
        return;
    }

    /*init states and derivatives with zero*/
    for(int i = 2; i < integratorSteps+integratorSteps; i++){
        handle->stateVec[i] = 0;
        handle->derivStateVec[i] = 0;
    }
}

void eulerForward(simHandle *handle)
{ // this is called only once
    int numOfStates = handle->numOfStates;
    int integratorSteps = (int)ceil(handle->simTime / handle->stepSize);
    double stepSize = handle->stepSize;
    double* derivativeTemporary;
    double* statesTemporary;

    derivativeTemporary = malloc(sizeof(double) * (handle->numOfStates));
    statesTemporary = malloc(sizeof(double) * (handle->numOfStates));

    /*write init states*/
    for (int i = 0; i < numOfStates; i++){
        handle->stateVec[i] = handle->stateVecInit[i];
    }
    for (int i = 0; i < integratorSteps; i++)
    {
        /*get derivatives*/
        for(int j = 0; j < numOfStates; j++){
            statesTemporary[j] = handle->stateVec[i+i+j];
        }
        handle->f(derivativeTemporary, statesTemporary);
        for(int k = 0; k < numOfStates; k++){
            handle->derivStateVec[i+i+k] = derivativeTemporary[k];
        }

        for(int j = 0; j < numOfStates; j++){
        	/*euler step*/
            //+2 because start values should not be overwritten
            handle->stateVec[i+i+2+j] = handle->stateVec[i+i+j] + (stepSize * handle->derivStateVec[i+i+j]);
        }
    }
}

void showResultsMSD(simHandle *handle)
{

    /*print data to text file*/
    FILE *fPtr;
    int integratorSteps = (int)ceil(handle->simTime / handle->stepSize);

    fPtr = fopen("simData.txt", "w");
    if(fPtr == NULL){
        printf("ERROR: file >>simData.txt<< couldnt be opened.");
        return;
    }
    else{
        for(int i = 0; i<integratorSteps; i++){
            fprintf(fPtr, "%lf ", i*handle->stepSize);
            fprintf(fPtr, "%lf ", handle->stateVec[i*2]);
            fprintf(fPtr, "%lf\n", handle->stateVec[i*2+1]);
        }

        fclose(fPtr);
    }

    /*call gnuplot*/
    generatePlot();
}

void generatePlot()
{
    FILE *gnuplotPipe;

    char *gnuPlotInput[] = {"set title 'Results of simulation'",

                            "set xlabel 'time in s'",

                            "plot 'simData.txt' using 1:2 title 'position',\
                            'simData.txt' using 1:3 title 'speed'"};

    gnuplotPipe = popen("gnuplot -persistent", "w");

    if(gnuplotPipe == NULL)
    {
        printf("ERROR: stream couldnt be opened.");
        return;
    }
    else
    {
        //fprintf(gnuplotPipe, "set xlabel 'time'\n");
        for(int i = 0; i < 3; i++){
            fprintf(gnuplotPipe, "%s\n", gnuPlotInput[i]);
        }

        fprintf(gnuplotPipe, "exit");
        pclose(gnuplotPipe);
    }
}
