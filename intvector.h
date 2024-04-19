#pragma once
#include "FieldInfo.h"

typedef struct VectorInt
{
    int size;
    void* elements;
    FieldInfo* vInfo;
} VectorInt;
VectorInt* createNewVectorInt(int*, FieldInfo*);
FieldInfo* createInfoInt();

void setVectorInt(VectorInt*);
void printVectorInt(VectorInt*);
void setToZeroInt(VectorInt*);
void freeVectorInt(VectorInt*);
void printElementInt(int*);

VectorInt* addUpVectorsInt(VectorInt*, VectorInt*);
VectorInt* scalarMultiplyInt(VectorInt*, VectorInt*);
VectorInt* multiplyByNumberInt(VectorInt*, int*);