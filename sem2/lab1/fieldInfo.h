#pragma once

typedef struct fieldInfo
{
    int elementSize;
    void* (*sumUp)(const void*, const void*, void*);
    void* (*multiply)(const void*, const void*, void*);
    void* (*getElement)(const void*, int);
    void* (*setToZero)(void*);
    char additional;
} fieldInfo;