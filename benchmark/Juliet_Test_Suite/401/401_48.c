// This is an open source non-commercial project. Dear PVS-Studio, please check it.
// PVS-Studio Static Code Analyzer for C, C++ and C#: http://www.viva64.com
/*
 * @description
 * CWE: 401 Memory Leak
 */

#include "401.h"

const int GLOBAL_CONST_TRUE = 1; /* true */
const int GLOBAL_CONST_FALSE = 0; /* false */
const int GLOBAL_CONST_FIVE = 5; 


int globalTrue = 1; /* true */
int globalFalse = 0; /* false */
int globalFive = 5; 

int globalReturnsTrue() 
{
    return 1;
}

int globalReturnsFalse() 
{
    return 0;
}

int globalReturnsTrueOrFalse() 
{
    return (rand() % 2);
}

void printLine (const char * line)
{
    if(line != NULL) 
    {
        printf("%s\n", line);
    }
}

void printIntLine (int intNumber)
{
    printf("%d\n", intNumber);
}

static const int STATIC_CONST_FIVE = 5;

#ifndef OMITBAD

void bad48()
{
    int * data;
    data = NULL;
    if(STATIC_CONST_FIVE==5)
    {
        /* POTENTIAL FLAW: Allocate memory on the heap */
        data = (int *)calloc(100, sizeof(int));
        if (data == NULL) return;
        /* Initialize and make use of data */
        data[0] = 5;
        printIntLine(data[0]);
    }
    if(STATIC_CONST_FIVE==5)
    {
        /* POTENTIAL FLAW: No deallocation */
        ; /* empty statement needed for some flow variants */
    }
}

#endif /* OMITBAD */

#ifndef OMITGOOD

void good48()
{
    int * data;
    data = NULL;
    if(STATIC_CONST_FIVE==5)
    {
        /* POTENTIAL FLAW: Allocate memory on the heap */
        data = (int *)calloc(100, sizeof(int));
        if (data == NULL) return;
        /* Initialize and make use of data */
        data[0] = 5;
        printIntLine(data[0]);
    }
    if(STATIC_CONST_FIVE!=5)
    {
        /* INCIDENTAL: CWE 561 Dead Code, the code below will never run */
        printLine("Benign, fixed string");
    }
    else
    {
        /* FIX: Deallocate memory */
        free(data);
    }
}
#endif /* OMITGOOD */

int main(){
    good48();
	bad48();
    return 1;
}