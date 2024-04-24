#pragma once
#include "FieldInfo.h"

typedef struct VectorReal
{
    int size;
    void* elements;
    FieldInfo* vInfo;
} VectorReal;
VectorReal* createNewVectorReal(int*);
FieldInfo* createInfoReal();

void setVectorReal(VectorReal*);
void printVectorReal(VectorReal*);
void setToZeroReal(VectorReal*);
void freeVectorReal(VectorReal*);
void printElementReal(float*);

VectorReal* addUpVectorsReal(VectorReal*, VectorReal*);
VectorReal* scalarMultiplyReal(VectorReal*, VectorReal*);
VectorReal* multiplyByNumberReal(VectorReal*, float*);