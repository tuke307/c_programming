#ifndef HA03_LINKEDLISTLIB_H_
#define HA03_LINKEDLISTLIB_H_

#include <stdbool.h>

#define FILE_LINE_FORMAT "%s %s %i\n"

/** 
    \STRUCT: listElement
 
    \AUTHOR: jannik wiessler

    \DATE: 2020-05-21

    \DESCRIPTION: definition of struct to create nodes from for the simple linked list 
*/
struct listElem{
    char lastName[50];
    char firstName[50];
    int age;
    struct listElem *nextElem;
};
typedef struct listElem listElement;

/** 
    \FUNCTION: addListElem
 
    \AUTHOR: jannik wiessler

    \DATE: 2020-05-21

    \DESCRIPTION: adds new entity of listElement to current list
 
    \param[in]  pointer to start element of current list              
*/
void addListElem(listElement *);

/** 
    \FUNCTION: printList
 
    \AUTHOR: jannik wiessler

    \DATE: 2020-05-21

    \DESCRIPTION: prints whole list to terminal
 
    \param[in]  pointer to start element of current list              
*/
void printList(listElement *);

/** 
    \FUNCTION: delListElem
 
    \AUTHOR: jannik wiessler

    \DATE: 2020-05-21

    \DESCRIPTION: deletes specific list element and free its memory
 
    \param[in]  pointer to start element of current list              
*/
void delListElem(listElement *);

/** 
    \FUNCTION: delList
 
    \AUTHOR: jannik wiessler

    \DATE: 2020-05-21

    \DESCRIPTION: deletes whole list and free its memory
 
    \param[in]  pointer to start element of current list              
*/
void delList(listElement *);

/** 
    \FUNCTION: getLenOfList
 
    \AUTHOR: jannik wiessler

    \DATE: 2020-05-21

    \DESCRIPTION: calculates the lenght of current list
 
    \param[in]  pointer to start element of current list        

    \param[out] lenght of current list
*/
int getLenOfList(listElement *);

/** 
    \FUNCTION: saveList
 
    \AUTHOR: jannik wiessler

    \DATE: 2020-05-21

    \DESCRIPTION: save current list to *.txt file which will be specified by the user.
 
    \param[in]  pointer to start element of current list        
*/
void saveList(listElement *);

/** 
    \FUNCTION: loadList
 
    \AUTHOR: jannik wiessler

    \DATE: 2020-05-21

    \DESCRIPTION: load a saved list from a *.txt file which will be specified by the user.
 
    \param[in]  pointer to start element of current list        
*/
void loadList(listElement *);

/** 
    \FUNCTION: exitFcn
 
    \AUTHOR: jannik wiessler

    \DATE: 2020-05-21

    \DESCRIPTION: asks user if the current list should be saved before program ends.
 
    \param[in]  pointer to start element of current list        
*/
void exitFcn(listElement *);

/** 
    \FUNCTION: sortList
 
    \AUTHOR: jannik wiessler

    \DATE: 2020-05-21

    \DESCRIPTION: sorts the list by fistName, lastName, or age. actual sorting criteria will be specified by the user.
 
    \param[in]  pointer to start element of current list        
*/
void sortList(listElement *);

/** 
    \FUNCTION: stringToLower
 
    \AUTHOR: jannik wiessler

    \DATE: 2020-05-21

    \DESCRIPTION: transforms any capital letters in a string to lower cases

    \param[in]  pointer to start element of current list        
*/
void stringToLower(char *); 

/** 
    \FUNCTION: appendList
 
    \AUTHOR: tony meissner

    \DATE: 2022-01-30

    \DESCRIPTION: add a new list element add the end of the linked list

    \param[in]  pointer to start element of current list

    \param[in]  lastname string

    \param[in]  firstname string

    \param[in]  age number       
*/
void appendList(listElement *, char[50], char[50], int);

/** 
    \FUNCTION: delListElemAtIndex
 
    \AUTHOR: tony meissner

    \DATE: 2022-01-30

    \DESCRIPTION: delete list element at specific index

    \param[in]  pointer to start element of current list  

    \param[in]  index of element to delete 

    \param[out]  exitCode exit_success (0) or exit_failure (1)        
*/
int delListElemAtIndex(listElement *, int);

/** 
    \FUNCTION: concatStr
 
    \AUTHOR: tony meissner

    \DATE: 2022-01-30

    \DESCRIPTION: combines two strings

    \param[in]  first pointer to string 

    \param[in]  second pointer to string

    \param[out]  combined pointer to string
*/
char* concatStr(const char*, const char*);

/** 
    \FUNCTION: fileExists
 
    \AUTHOR: tony meissner

    \DATE: 2022-01-30

    \DESCRIPTION: checks if file exists

    \param[in]  pointer to filename or filepath

    \param[out] exists the file
*/
bool fileExists(char *);

#endif