#include "fieldInfo.h"
#include "intvector.h"
#include "number.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void* sumUpInt(const void *arg1, const void *arg2, void *result)
{
    int* first = (int*) arg1;
    int* second = (int*) arg2;
    *((int*) result) = *first + *second;
    return result;
}

void* multiplyInt(const void* arg1, const void* arg2, void* result)
{
    int* first = (int*) arg1;
    int* second = (int*) arg2;
    *((int*) result) = *first * *second;
    return result;
}

void* setToZeroInt(void* arg)
{
    *((int*) arg) = 0;
    return arg;
}

void* getElementInt(const void* elements, int index)
{
    int* element = ((int*) elements + index);
    return (void*) element;
}

fieldInfo* getInfoInt()
{
    static fieldInfo* info = NULL;
    if (info == NULL)
    {
        info = malloc(sizeof(fieldInfo));
        if (info == NULL)
        {
            printf("in intvector.c in getinfoint: allocation error\n");
            exit(-1);
        }
        info->elementSize = sizeof(int);
        info->sumUp = sumUpInt;
        info->multiply = multiplyInt;
        info->getElement = getElementInt;
        info->setToZero = setToZeroInt;
        info->additional = 'i';
    }
    return info;
}