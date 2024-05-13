#include "fieldInfo.h"
#include "intvector.h"
#include "realvector.h"
#include "number.h"
#include <stdio.h>
#include <stdlib.h>

typedef struct vector
{
    int size;
    void* elements;
    fieldInfo* info;
} vector;

int compareFieldInfo(fieldInfo* a, fieldInfo* b)
{
    int result = 1;
    if (a->additional != b->additional)
    {
        result = 0;
    }
    return result;
}

void setToZero(vector* v)
{
    void* arg;
    for (int i = 0; i < v->size; i++)
    {
        arg = v->info->getElement(v->elements, i);
        v->info->setToZero(arg);
    }
    return;
}

vector* createNewVector(int* dimension, fieldInfo* info)
{
    vector* v = malloc(sizeof(vector));
    if (v == NULL)
    {
        printf("vector allocation error\n");
        exit(-1);
    }
    v->size = *dimension;
    v->elements = (int*) malloc(v->size * info->elementSize);
    if (v->elements == NULL)
    {
        printf("elements allocation error\n");
        exit(-1);
    }
    v->info = info;
    setToZero(v);
    return v;
}

void printElement(fieldInfo* info, void *element)
{
    if (info->additional == 'i' || info->additional == 't')
    {
        printf("%d", *((int*) element));
    }
    else if (info->additional == 'r')
    {
        printf("%f", *((float*) element));
    }
    else
    {
        printf("undefined fieldInfo (vector.c:70)\n");
    }
    return;
}

void printVector(vector* v)
{
    for (int i = 0; i < v->size - 1; i ++)
    {
        printElement(v->info, v->info->getElement(v->elements, i));
        printf(" ");
    }
    printElement(v->info, v->info->getElement(v->elements, v->size - 1));
    printf("\n");
    return;
}

void freeVector(vector* v)
{
    free(v->elements);
    free(v);
    return;
}

vector* sumUpVectors(vector* a, vector* b)
{
    void* arg1;
    void* arg2;
    void* result;
    if (compareFieldInfo(a->info, b->info) == 0)
    {
        printf("function cannot add up vectors of different types\n");
        return NULL;
    }
    int maxLength = a->size;
    int minLength = b->size;
    if (b->size > maxLength)
    {
        maxLength = b->size;
        minLength = a->size;
    }
    vector* c = createNewVector(&maxLength, a->info);
    for (int i = 0; i < minLength; i++)
    {
        arg1 = a->info->getElement(a->elements, i);
        arg2 = a->info->getElement(b->elements, i);
        result = a->info->getElement(c->elements, i);
        a->info->sumUp(arg1, arg2, result);
    }
    for (int i = minLength; i < maxLength; i++)
    {
        result = a->info->getElement(c->elements, i);
        if (maxLength == b->size)
        {
            arg1 = a->info->setToZero(arg1);
            arg2 = b->info->getElement(b->elements, i);
            a->info->sumUp(arg1, arg2, result);
        }
        else
        {
            arg1 = a->info->getElement(a->elements, i);
            arg2 = a->info->setToZero(arg2);
            a->info->sumUp(arg1, arg2, result);
        }
    }
    return c;
}

vector* scalarMultiplyVectors(vector* a, vector* b)
{
    void* arg1;
    void* arg2;
    void* result;
    if (compareFieldInfo(a->info, b->info) == 0)
    {
        printf("function cannot add up vectors of different types\n");
        return NULL;
    }
    int maxLength = a->size;
    int minLength = b->size;
    if (b->size > maxLength)
    {
        maxLength = b->size;
        minLength = a->size;
    }
    vector* c = createNewVector(&maxLength, a->info);
    for (int i = 0; i < minLength; i++)
    {
        arg1 = a->info->getElement(a->elements, i);
        arg2 = a->info->getElement(b->elements, i);
        result = a->info->getElement(c->elements, i);
        a->info->multiply(arg1, arg2, result);
    }
    for (int i = minLength; i < maxLength; i++)
    {
        result = c->info->getElement(c->elements, i);
        c->info->setToZero(result);
    }
    return c;
}

vector* multiplyByNumber(vector* a, void* arg2)
{
    void* arg1;
    void* result;
    vector* b = createNewVector(&a->size, a->info);
    for (int i = 0; i < b->size; i++)
    {
        arg1 = a->info->getElement(a->elements, i);
        result = a->info->getElement(b->elements, i);
        a->info->multiply(arg1, arg2, result);
    }
    return b;
}

void* enterCoefficient(int size, void* elements, char data)
{
    printf("get ready\n");
    if (data == 'i' || data == 't')
    {
        for (int i = 0; i < size; i++)
        {
            printf("enter %d int coefficient\n", i+1);
            *(((int*) elements) + i) = readIntNumb();
        }
    }
    else if (data == 'r')
    {
        for (int i = 0; i < size; i++)
        {
            printf("enter %d real coefficient\n", i+1);
            *(((float*) elements) + i) = readFloatNumb();
        }
    }
    else
    {
        printf("unknown data\n");
        exit(-1);
    }
    return elements;
}

void* getElements(vector* v)
{
    return v->elements;
}

int getSize(vector* v)
{
    return v->size;
}

char getAdditionalData(vector* v)
{
    return v->info->additional;
}

fieldInfo* getInfo(vector* v)
{
    return v->info;
}