#include "FieldInfo.h"
#include "intvector.h"
#include "number.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

FieldInfo* createInfoInt()
{
    FieldInfo* info = malloc(sizeof(FieldInfo));
    if (info == NULL)
    {
        printf("allocation error\n");
        exit(-1);
    }
    info->elementSize = sizeof(int);
    info->addUpVector = (void*) addUpVectorsInt;
    info->createNewVector = (void*) createNewVectorInt;
    info->multiplyByNumber = (void*) multiplyByNumberInt;
    info->printElement = (void*) printElementInt;
    info->scalarMultiply = (void*) scalarMultiplyInt;
    return info;
}

void printElementInt(int* element)
{
    printf("%d", (int)(*element));
    return;
}

VectorInt* createNewVectorInt(int* size, FieldInfo* info)
{
    printf("creating vector\n");
    VectorInt* v = malloc(sizeof(VectorInt));
    v->size = *size;
    v->elements = (int*) malloc(v->size * info->elementSize);
    v->vInfo = info;
    if (v == NULL)
    {
        printf("vector allocation error\n");
        exit(-1);
    }
    if (v->elements == NULL)
    {
        printf("elements allocation error\n");
        exit(-1);
    }
    printf("setting to zero\n");
    setToZeroInt(v);
    return v;
}

void setVectorInt(VectorInt* v)
{
    printf("enter %d numbers - vector coordinates\n", v->size);
    for (int i = 0; i < v->size; i++)
    {
        printf("please enter %d coordinate\n", i+1);
        int d = readIntNumb();
        *((int*)(v->elements)+i) = d;
    }
    return;
}

void printVectorInt(VectorInt* v)
{
    for (int i = 0; i < v->size; i++)
    {
        printElementInt(((int*)(v->elements)+i));
        if (i + 1 != v->size)
        {
            printf(" ");
        }
        else
        {
            printf("\n");
        }
    }
    return;
}

void setToZeroInt(VectorInt* v)
{
    for (int i = 0; i < v->size; i++)
    {
        *((int*)(v->elements)+i) = 0;
    }
    return;
}

void freeVectorInt(VectorInt* v)
{
    free((int*)v->elements);
    free(v);
    return;
}

VectorInt* addUpVectorsInt(VectorInt* a, VectorInt* b)
{
    printf("adding up vector\n");
    int maxLength = a->size;
    int minLength = b->size;
    if (b->size > maxLength)
    {
        maxLength = b->size;
        minLength = a->size;
    }
    VectorInt* c = createNewVectorInt(&maxLength, a->vInfo);
    for (int i = 0; i < minLength; i++)
    {
        *((int*)(c->elements)+i) = *((int*)(a->elements)+i) + *((int*)(b->elements)+i);
    }
    for (int i = minLength; i < maxLength; i++)
    {
        if (maxLength == b->size)
        {
            *((int*)(c->elements)+i) = *((int*)(b->elements)+i);
        }
        else
        {
            *((int*)(c->elements)+i) = *((int*)(a->elements)+i);
        }
    }
    return c;
}

VectorInt* scalarMultiplyInt(VectorInt* a, VectorInt* b)
{
    printf("making scalar Multyplying\n");
    int maxLength = a->size;
    int minLength = b->size;
    if (b->size > maxLength)
    {
        maxLength = b->size;
        minLength = a->size;
    }
    VectorInt* c = createNewVectorInt(&maxLength, a->vInfo);
    for (int i = 0; i < minLength; i++)
    {
        *((int*)(c->elements)+i) = *((int*)(a->elements)+i) * *((int*)(b->elements)+i);
    }
    for (int i = minLength; i < maxLength; i++)
    {
        *((int*)(c->elements)+i) = 0;
    }
    return c;
}

VectorInt* multiplyByNumberInt(VectorInt* a, int* number)
{
    printf("multiplying by number\n");
    VectorInt* b = createNewVectorInt(&a->size, a->vInfo);
    for (int i = 0; i < b->size; i++)
    {
        *((int*)(b->elements)+i) = *((int*)(a->elements)+i) * *number;
    }
    return b;
}
