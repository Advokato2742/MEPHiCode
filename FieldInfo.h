#pragma once

typedef struct FieldInfo
{
    int elementSize;
    void* (*addUpVector)(void*,void*);
    void* (*scalarMultiply)(void*, void*);
    void* (*multiplyByNumber)(void*, void*);
    void* (*createNewVector)(void*, void*);
    void* (*scalarZero)();
    void* (*printElement)(void*);
} FieldInfo;

extern FieldInfo* infoInt;
extern FieldInfo* infoReal;