#include "FieldInfo.h"
#include "vector.h"
#include "number.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

FieldInfo* createInfo()
{
    FieldInfo* info = malloc(sizeof(FieldInfo));
    if (info == NULL)
    {
        printf("allocation error\n");
        exit(-1);
    }
    info->elementSize = sizeof(float);
    info->addUpVector = (void*)addUpVector;
    info->createNewVector = (void*)createNewVector;
    info->multiplyByNumber = (void*)multiplyByNumber;
    info->printElement = (void*)printElement;
    info->scalarMultiply = (void*)scalarMultiply;
    return info;
}

void printElement(float* element)
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

Vector* createNewVector(int* size, FieldInfo* info)
{
    printf("creating vector\n");
    Vector* v = malloc(sizeof(Vector));
    v->size = *size;
    v->elements = (float*)malloc(v->size* info->elementSize);
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
    setToZero(v);
    return v;
}

void setVector(Vector* v)
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

void printVector(Vector* v)
{
    for (int i = 0; i < v->size; i++)
    {
        printElement(((float*)(v->elements)+i));
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

void setToZero(Vector* v)
{
    for (int i = 0; i < v->size; i++)
    {
        *((float*)(v->elements)+i) = 0;
    }
    return;
}

void freeVector(Vector* v)
{
    free((float*)v->elements);
    free(v);
    return;
}

Vector* addUpVector(Vector* a, Vector* b)
{
    printf("adding up vector\n");
    int maxLength = a->size;
    int minLength = b->size;
    if (b->size > maxLength)
    {
        maxLength = b->size;
        minLength = a->size;
    }
    Vector* c = createNewVector(&maxLength, a->vInfo);
    for (int i = 0; i < minLength; i++)
    {
        *((float*)(c->elements)+i) = *((float*)(a->elements)+i) + *((float*)(b->elements)+i);
    }
    for (int i = minLength; i < maxLength; i++)
    {
        *((float*)(c->elements)+i) = *((float*)(b->elements)+i);
    }
    return c;
}

Vector* scalarMultiply(Vector* a, Vector* b)
{
    printf("making scalar Multyplying\n");
    int maxLength = a->size;
    int minLength = b->size;
    if (b->size > maxLength)
    {
        maxLength = b->size;
        minLength = a->size;
    }
    Vector* c = createNewVector(&maxLength, a->vInfo);
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

Vector* multiplyByNumber(Vector* a, float* number)
{
    printf("multiplying by number\n");
    Vector* b = createNewVector(&a->size, a->vInfo);
    for (int i = 0; i < b->size; i++)
    {
        *((float*)(b->elements)+i) = *((float*)(a->elements)+i) * *number;
    }
    return b;
}