#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "linkedListLib.h"

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

    int index; 
    listElement* current = start;
    listElement* previous = NULL;

    if (start->nextElem == NULL)
        printf("List is empty.\n");
    else
    {
        printf("enter the index of the item, you want to delete: \n");
        scanf("%i", &index);

        for (int i = 0; i < index; i++) {
            if (start->nextElem == NULL) {
                return;
            }

            start = start->nextElem;
        }

        if (start->nextElem == NULL) {
            return;
        }

        // found a match, update the link
        if(current == start) {
            //change first to point to next link
            start = start->nextElem;
        } else {
            //bypass the current link
            previous->nextElem = current->nextElem;
        }    
            
        start = current;
    }
}

void delList(listElement *start)
{
    struct listElement* prev = start;
 
    while (start)
    {
        start = start->nextElem;

        free(prev);
        prev = start;
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
    char filename[50];  
    FILE *outfile;
     
    if (start->nextElem == NULL)
        printf("List is empty.\n");
    else
    {
        // open file for writing
        printf("filename: ");
        scanf("%s", &filename);
        outfile = fopen (filename, "w");
        if (outfile == NULL)
        {
            fprintf(stderr, "\nError opening file\n");
            exit (1);
        }

        listElement *currElem = start;
        do
        {
            currElem = currElem->nextElem;
            // write strcut to file
            fwrite (&currElem, sizeof(listElement), 1, outfile);
        } while (currElem->nextElem != NULL);

        if(fwrite != 0)
            printf("contents to file written successfully !\n");
        else
            printf("error writing file !\n");
    
        fclose (outfile);
    }
     
    
}
void appendList(
    listElement** head_ref,
    listElement insert)
{
    /* 1. allocate node */
    listElement* new_node = (listElement*) malloc(sizeof(listElement));

    listElement *last = *head_ref;  /* used in step 5*/

    /* 2. put in the data  */
    strcpy(new_node->lastName,insert.lastName);
    strcpy(new_node->firstName, insert.firstName);
    new_node->age  = insert.age;

    /* 3. This new node is going to be the last node, so make next of
          it as NULL*/
    new_node->nextElem = NULL;

    /* 4. If the Linked List is empty, then make the new node as head */
    if (*head_ref == NULL)
    {
       *head_ref = new_node;
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
    FILE *infile;
    listElement input;
    char filename[50];
     
    system("dir *.txt");
    printf("filename: ");
    scanf("%s", &filename);

    infile = fopen (filename, "r");
    if (infile == NULL)
    {
        fprintf(stderr, "\nError opening file\n");
    }
     
    // read file contents till end of file
    while(fread(&input, sizeof(listElement), 1, infile))
        appendList(start, input);
 
    // close file
    fclose (infile);


    printf("loading data will be append to current list...\n");
    printList(start); // show loaded list
}

void exitFcn(listElement *start)
{
    
    printf("\n>> exitFcn fcn is tbd.\n\n");
}

void sortList(listElement *start)
{

    printf("\n>>sortList fcn is tbd.\n\n");
}

void stringToLower(char *string)
{

    printf("\n>>stringToLower fcn is tbd.\n\n");
}
