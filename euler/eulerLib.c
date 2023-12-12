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

    /*num of states*/
    handle->numOfStates = (int)NUMOFSTATES;

    /*right hand site*/
    handle->f = rhsMSD;

    /*reserve storage for init state vec*/
    handle->stateVecInit = malloc((handle->numOfStates) * sizeof(double));
    if(handle->stateVecInit == NULL){
        printf("ERROR: can't allocate space.\n");
        return;
    }

    /*get user defined Simtime*/
    printf("Simtime (in s): \n");
    scanf(" %lf", &handle->simTime);
    if(handle->simTime < 0){
        printf("ERROR: invalid input for simtime, simtime must not be negative or zero\n");
        return;
    }

    /*get user defined StepSize*/
    printf("StepSize (in s): \n");
    scanf(" %lf", &handle->stepSize);
    if (handle->stepSize < 0){
        printf("ERROR: invalid input for stepsize, stepsize must not be negative or zero\n");
        return;
    }

    /*get init state position*/
    printf("position(t = 0): \n");
    scanf(" %lf", &handle->stateVecInit[0]);
    
    /*get init state speed*/
    printf("speed(t = 0): \n");
    scanf(" %lf", &handle->stateVecInit[1]);

    /*reserve storage for states and derivatives*/
    handle->stateVec = malloc( ceil((handle->simTime / handle->stepSize)) * (handle->numOfStates) * sizeof(double));
    if(handle->stateVec == NULL){
        printf("ERROR: can't allocate space.\n");
        return;
    }

    handle->derivStateVec = malloc( ceil((handle->simTime / handle->stepSize)) * (handle->numOfStates) * sizeof(double));
    if(handle->derivStateVec == NULL){
        printf("ERROR: can't allocate space.\n");
        return;
    }

    /*init states and derivatives with zero*/
    for(int i = 0; i < ceil((handle->simTime / handle->stepSize)) * (handle->numOfStates); i++){
        handle->stateVec[i] = 0;
        handle->derivStateVec[i] = 0;
    }
}

void eulerForward(simHandle *handle)
{ // this is called only once
    int numOfStates = handle->numOfStates;
    int integratorSteps = ceil(handle->simTime / handle->stepSize)*handle->numOfStates;
    double* tempPos = malloc(sizeof(double) * (numOfStates));
    double* tempVel = malloc(sizeof(double) * (numOfStates));
    double temp = 0;
    
    /*write init states*/
    for (int i = 0; i < numOfStates; i++){
        handle->stateVec[i] = handle->stateVecInit[i];
    }
    for (int i = 0; i < integratorSteps; i=i+handle->numOfStates)
    {
        /*get derivatives*/
        for(int k = 0; k < numOfStates; k++)
		{
            tempPos[k] = handle->stateVec[i+k];
    	}

        handle->f(tempVel, tempPos);

		for(int j = 0; j < numOfStates; j++)
		{
			temp = handle->stateVec[i+j] + handle->stepSize * tempVel[j];
            handle->stateVec[i+handle->numOfStates+j] = temp;
    	}
    }
}

void showResultsMSD(simHandle *handle)
{

    /*print data to text file*/
    FILE *fPtr;
    int integratorSteps = ceil(handle->simTime / handle->stepSize);
    fPtr = fopen("simData.txt", "w");
    if(fPtr == NULL){
        printf("ERROR: file >>simData.txt<< couldnt be opened.");
        return;
    }
    else{
        for(int i = 0; i < integratorSteps; i++){
            
            fprintf(fPtr, "%lf ", i*handle->stepSize);
            fprintf(fPtr, "%lf ", handle->stateVec[i+i]);
            fprintf(fPtr, "%lf\n", handle->stateVec[i+i+1]);
        }

        
    }

    fclose(fPtr);

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
