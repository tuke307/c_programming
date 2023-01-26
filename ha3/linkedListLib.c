#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedListLib.h"

void appendList(listElement *, listElement);

int delListElemAtIndex(listElement *, int);

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
        printf("nothing to delete: list is alredy empty.\n");
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
        printf("nothing to delete: list is alredy empty.\n");
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

void saveList(listElement *start)
{
    char saveFilename[50];  
    FILE *listSaveFile;
    listElement *current = start;
    char fileSaveFormat[100] = "%s,%s,%i\n";

    if (current->nextElem == NULL)
        printf("List is empty.\n");
    else
    {
        printf("filename: ");
        scanf("%s", saveFilename);

        listSaveFile = fopen (saveFilename, "w");
        if (listSaveFile == NULL)
        {
            printf("Error opening file\n");
        }else
        {
            do
            {
                current = current->nextElem;
                fprintf (listSaveFile, fileSaveFormat, current->lastName, current->firstName, current->age);
            } while (current->nextElem != NULL);
        
            fclose (listSaveFile);
        }
    }
}

void appendList(
    listElement* start,
    listElement insert)
{
    /* 1. allocate node */
    listElement* new_node = (listElement*) malloc(sizeof(listElement));

    listElement *last = start;  /* used in step 5*/

    /* 2. put in the data  */
    strcpy(new_node->lastName,insert.lastName);
    strcpy(new_node->firstName, insert.firstName);
    new_node->age  = insert.age;

    /* 3. This new node is going to be the last node, so make next of
          it as NULL*/
    new_node->nextElem = NULL;

    /* 4. If the Linked List is empty, then make the new node as head */
    if (start == NULL)
    {
       start = new_node;
       return;
    }

    /* 5. Else traverse till the last node */
    while (last->nextElem != NULL)
        last = last->nextElem;

    /* 6. Change the next of last node */
    last->nextElem = new_node;

    return;
}

void loadList(listElement *start)
{
    FILE *listFile;
    listElement input;
    char filename[50];
    char fileSaveFormat[100] = "%s,%s,%i";
    char line[100];

    system("dir *.txt");
    printf("filename: ");
    scanf("%s", filename);

    listFile = fopen (filename, "r");
    if (listFile == NULL)
    {
        printf("Error opening file\n");
    }
    
    printf("loading data will be append to current list...\n");

    while (fgets(line, 100, listFile)) {
        sscanf(line, fileSaveFormat, input.lastName, input.firstName, input.age);
        appendList(start, input);
    }

    fclose (listFile);

    printList(start); // show loaded list
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
