#include "fieldInfo.h"
#include "intvector.h"
#include "number.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void* sumUpInt(void *arg1, void *arg2, void *result)
{
    int* first = (int*) arg1;
    int* second = (int*) arg2;
    *((int*) result) = *first + *second;
    return result;
}

void* multiplyInt(void* arg1,  void* arg2, void* result)
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

void* getElementInt(void* elements, int index)
{
    int* element = ((int*) elements + index);
    return (void*) element;
}

fieldInfo* createInfoInt()
{
    fieldInfo* info = malloc(sizeof(fieldInfo));
    if (info == NULL)
    {
        printf("allocation error\n");
        exit(-1);
    }
    info->elementSize = sizeof(int);
    info->sumUp = sumUpInt;
    info->multiply = multiplyInt;
    info->getElement = getElementInt;
    info->setToZero = setToZeroInt;
    info->additional = 'i';
    return info;
}