#pragma once
#include "FieldInfo.h"

typedef struct Vector
{
    int size;
    void* elements;
    FieldInfo* vInfo;
} Vector;
Vector* createNewVector(int*, FieldInfo*);

void setVector(Vector*);
void printVector(Vector*);
void setToZero(Vector*);
void freeVector(Vector*);
void printElement(float*);

Vector* addUpVector(Vector*, Vector*);
Vector* scalarMultiply(Vector*, Vector*);
Vector* multiplyByNumber(Vector*, float*);