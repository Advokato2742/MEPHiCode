#include "fieldInfo.h"
#include "realvector.h"
#include "number.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

void* sumUpReal(void *arg1, void *arg2, void *result)
{
    float* first = (float*) arg1;
    float* second = (float*) arg2;
    *((float*) result) = *first + *second;
    return result;
}

void* multiplyReal(void* arg1,  void* arg2, void* result)
{
    float* first = (float*) arg1;
    float* second = (float*) arg2;
    *((float*) result) = *first * *second;
    return result;
}

void* setToZeroReal(void* arg)
{
    *((float*) arg) = 0;
    return arg;
}

void* getElementReal(void* elements, int index)
{
    float* element = ((float*) elements + index);
    return (void*) element;
}

fieldInfo* createInfoReal()
{
    fieldInfo* info = malloc(sizeof(fieldInfo));
    if (info == NULL)
    {
        printf("allocation error\n");
        exit(-1);
    }
    info->elementSize = sizeof(float);
    info->sumUp = sumUpReal;
    info->multiply = multiplyReal;
    info->getElement = getElementReal;
    info->setToZero = setToZeroReal;
    info->additional = 'r';
    return info;
}