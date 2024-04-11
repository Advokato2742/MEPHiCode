#pragma once

typedef struct FieldInfo
{
    int elementSize;
    void* (*addUpVector)(void*,void*);
    void* (*scalarMultiply)(void*, void*);
    void* (*multiplyByNumber)(void*, void*);
    void* (*createNewVector)(void*, void*);
    void* (*printElement)(void*);
} FieldInfo;

FieldInfo* createInfo();