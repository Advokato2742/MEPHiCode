#pragma once

typedef struct fieldInfo
{
    int elementSize;
    void* (*sumUp)(void*, void*, void*);
    void* (*multiply)(void*, void*, void*);
    void* (*getElement)(void*, int);
    void* (*setToZero)();
    char additional;
} fieldInfo;