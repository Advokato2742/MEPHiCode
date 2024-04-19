#include "FieldInfo.h"
#include "realvector.h"
#include "number.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

FieldInfo* createInfoReal()
{
    FieldInfo* info = malloc(sizeof(FieldInfo));
    if (info == NULL)
    {
        printf("allocation error\n");
        exit(-1);
    }
    info->elementSize = sizeof(float);
    info->addUpVector = (void*) addUpVectorsReal;
    info->createNewVector = (void*) createNewVectorReal;
    info->multiplyByNumber = (void*) multiplyByNumberReal;
    info->printElement = (void*) printElementReal;
    info->scalarMultiply = (void*) scalarMultiplyReal;
    return info;
}

void printElementReal(float* element)
{
    float a = fabs(*element);
    if (a - (int) a < 0.0001)
    {
        printf("%d", (int)(*element));
    }
    else
    {
        printf("%.4f", *element);
    }
    return;
}

VectorReal* createNewVectorReal(int* size, FieldInfo* info)
{
    printf("creating vector\n");
    VectorReal* v = malloc(sizeof(VectorReal));
    v->size = *size;
    v->elements = (float*) malloc(v->size * info->elementSize);
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
    setToZeroReal(v);
    return v;
}

void setVectorReal(VectorReal* v)
{
    printf("enter %d numbers - vector coordinates\n", v->size);
    for (int i = 0; i < v->size; i++)
    {
        printf("please enter %d coordinate\n", i+1);
        float d = readFloatNumb();
        *((float*)(v->elements)+i) = d;
    }
    return;
}

void printVectorReal(VectorReal* v)
{
    for (int i = 0; i < v->size; i++)
    {
        printElementReal(((float*)(v->elements)+i));
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

void setToZeroReal(VectorReal* v)
{
    for (int i = 0; i < v->size; i++)
    {
        *((float*)(v->elements)+i) = 0;
    }
    return;
}

void freeVectorReal(VectorReal* v)
{
    free((float*)v->elements);
    free(v);
    return;
}

VectorReal* addUpVectorsReal(VectorReal* a, VectorReal* b)
{
    printf("adding up vector\n");
    int maxLength = a->size;
    int minLength = b->size;
    if (b->size > maxLength)
    {
        maxLength = b->size;
        minLength = a->size;
    }
    VectorReal* c = createNewVectorReal(&maxLength, a->vInfo);
    for (int i = 0; i < minLength; i++)
    {
        *((float*)(c->elements)+i) = *((float*)(a->elements)+i) + *((float*)(b->elements)+i);
    }
    for (int i = minLength; i < maxLength; i++)
    {
        if (maxLength == b->size)
        {
            *((float*)(c->elements)+i) = *((float*)(b->elements)+i);
        }
        else
        {
            *((float*)(c->elements)+i) = *((float*)(a->elements)+i);
        }
    }
    return c;
}

VectorReal* scalarMultiplyReal(VectorReal* a, VectorReal* b)
{
    printf("making scalar Multyplying\n");
    int maxLength = a->size;
    int minLength = b->size;
    if (b->size > maxLength)
    {
        maxLength = b->size;
        minLength = a->size;
    }
    VectorReal* c = createNewVectorReal(&maxLength, a->vInfo);
    for (int i = 0; i < minLength; i++)
    {
        *((float*)(c->elements)+i) = *((float*)(a->elements)+i) * *((float*)(b->elements)+i);
    }
    for (int i = minLength; i < maxLength; i++)
    {
        *((float*)(c->elements)+i) = 0;
    }
    return c;
}

VectorReal* multiplyByNumberReal(VectorReal* a, float* number)
{
    printf("multiplying by number\n");
    VectorReal* b = createNewVectorReal(&a->size, a->vInfo);
    for (int i = 0; i < b->size; i++)
    {
        *((float*)(b->elements)+i) = *((float*) (a->elements) + i) * *number;
    }
    return b;
}