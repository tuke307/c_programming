#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>   // only win
#include <stdbool.h>
#include "linkedListLib.h"

void appendList(listElement *, char[50], char[50], int);

int delListElemAtIndex(listElement *, int);

const char *getFilenameExt(const char *);

char* concatStr(const char*, const char*);

bool fileExists(char *);

char* concatStr(const char* strFirst, const char* strSecond)
{
    char *result = malloc(strlen(strFirst) + strlen(strSecond) + 1);
    strcpy(result, strFirst);
    strcat(result, strSecond);
    return result;
}

void addListElem(listElement *start)
{

    listElement *new;
    new = (listElement *)malloc(sizeof(listElement));
    if (new == NULL)
    {
        printf("can't reserve storage.\n");
        return;
    }

    listElement *currElem = start;
    while (currElem->nextElem != NULL)
        currElem = currElem->nextElem; // get last elem in list
    currElem->nextElem = new;          // add new to the end of list
    new->nextElem = NULL;

    /* fill data in new element */
    printf("Please enter last name: \n");
    scanf("%s", new->lastName);
    printf("Please enter first name: \n");
    scanf("%s", new->firstName);
    printf("Please enter age: \n");
    scanf("%d", &(new->age));
}

void printList(listElement *start)
{

    if (start->nextElem == NULL)
        printf("List is empty.\n");
    else
    {
        int i = 0;
        listElement *currElem = start;
        printf("\ncurrent list:\n\n");
        do
        {
            currElem = currElem->nextElem;
            printf("%d", i);
            i++;
            printf("\t last name: %s\n", currElem->lastName);
            printf("\t first name: %s\n", currElem->firstName);
            printf("\t age: %d\n", currElem->age);
        } while (currElem->nextElem != NULL);
    }
}

void delListElem(listElement *start)
{

    int indexElementDelete;

    if (start->nextElem == NULL)
        printf("nothing to delete, list is alredy empty.\n");
    else
    {
        printList(start);
        printf("enter the index of the item, you want to delete: ");
        scanf("%i", &indexElementDelete);
        if(delListElemAtIndex(start, indexElementDelete) == EXIT_SUCCESS)
            printf("deleted element with index %i\n", indexElementDelete);
    }
}

int delListElemAtIndex(listElement *start, int indexElementDelete)
{
    listElement* current = start;
    listElement* previous = NULL;

    if(indexElementDelete > getLenOfList(current) - 1)
        printf("index is out of range.\n");
    else
    {
        for (int i = 0; i < indexElementDelete; i++)
            current = current->nextElem;

        // found a match, update the element
        previous = current->nextElem;
        current->nextElem = previous->nextElem;
        free(previous);

        return EXIT_SUCCESS;
    }
    
    return EXIT_FAILURE;
}

void delList(listElement *start)
{
    if (start->nextElem == NULL)
        printf("nothing to delete, list is alredy empty.\n");
    else
    {
        // delete backwards by index
        for (int index = getLenOfList(start) - 1; index >= 0; index--)
        {
            delListElemAtIndex(start, index);
        }

        if (start == NULL) {
            printf("list deleted.\n");
        }
    }
}

int getLenOfList(listElement *start)
{ // we use this for save list fcn

    int counter = 0;
    listElement *currElem = start;
    while (currElem->nextElem != NULL)
    { // get last elem in list
        currElem = currElem->nextElem;
        counter++;
    }
    return counter;
}

const char *getFilenameExt(const char *filename)
{
    const char *dot = strrchr(filename, '.');
    if(!dot || dot == filename)
        return "";
    return dot + 1;
}

bool fileExists(char *filename) {
  struct stat   buffer;   
  return (stat (filename, &buffer) == 0);
}

void saveList(listElement *start)
{
    char *saveFilename = (char*)malloc(sizeof(char)); 
    FILE *filePtr;
    listElement *current = start;
    char *fileLineFormat = "%s %s %i\n";

    if (current->nextElem == NULL)
        printf("nothing to save, list is empty.\n");
    else{
        printf("filename (without extension): ");
        scanf("%s", saveFilename);
        saveFilename = concatStr(saveFilename, ".txt");

        filePtr = fopen (saveFilename, "w");
        if (filePtr == NULL)
            printf("ERROR: while opening file.\n");
        else{
            do{
                current = current->nextElem;
                fprintf (filePtr, fileLineFormat, current->lastName, current->firstName, current->age);
            } while (current->nextElem != NULL);

            fclose (filePtr);

            printf("list was successfully saved in >>%s<<.\n", saveFilename);
        }
    }
}

void appendList(listElement* start, char lastName[50], char firstName[50], int age)
{
    listElement* newElem = (listElement*) malloc(sizeof(listElement));
    listElement *lastElem = start;

    strcpy(newElem->lastName, lastName);
    strcpy(newElem->firstName, firstName);
    newElem->age = age;

    newElem->nextElem = NULL;

    if (start == NULL){
       start = newElem;
       return;
    }

    while (lastElem->nextElem != NULL)
        lastElem = lastElem->nextElem;

    lastElem->nextElem = newElem;
}

void loadList(listElement *start)
{
    FILE *filePtr;
    char *filename = (char*)malloc(sizeof(char));
    //char *fileLineFormat = "%s %s %i";
    char *line = (char*)malloc(sizeof(char));
    char lastName[50];
    char firstName[50];
    int age = 0;

    system("dir *.txt");
    printf("filename (without extension): ");
    scanf("%s", filename);
    filename = concatStr(filename, ".txt");

    if(!fileExists(filename))
        printf("ERROR: file not found.\n");
    else{
        filePtr = fopen (filename, "r");
        if (filePtr == NULL)
            printf("ERROR: while opening file.\n");
        else{
            printf("loading data will be append to current list...\n");

            while (fgets(line, 100, filePtr)) {
                // TODO: use fscanf!
                sscanf(line, "%s %s %i", &lastName[0], &firstName[0], &age);
                appendList(start, lastName, firstName, age);
            }

            fclose (filePtr);

            printList(start); // show loaded list
        }
    }
}

void exitFcn(listElement *start)
{

    char answer = 'n';

    printf("do you want to safe the progress? (y/n).\n");
    scanf(" %c", &answer);

    if(answer == 'y')
    {
        saveList(start);
    }
}

void sortList(listElement *start)
{

    printf("\n>>sortList fcn is tbd.\n\n");
}

void stringToLower(char *string)
{

    printf("\n>>stringToLower fcn is tbd.\n\n");
}
