#pragma once
#include "fieldInfo.h"

typedef struct vector vector;

void setToZero(vector* v);
void freeVector(vector* v);
void printElement(fieldInfo* info, void *element);
void printVector(vector* v);
int compareFieldInfo(fieldInfo* a, fieldInfo* b);
void* enterCoefficient(int size, void* elements, char data);
void* getElements(vector* v);
int getSize(vector* v);
char getAdditionalData(vector* v);
fieldInfo* getInfo(vector* v);

vector* createNewVector(int* dimension, fieldInfo* info);
vector* sumUpVectors(vector* a, vector* b);
vector* scalarMultiplyVectors(vector* a, vector* b);
vector* multiplyByNumber(vector* a, void* arg);