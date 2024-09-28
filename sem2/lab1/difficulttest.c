#include "difficulttest.h"
#include "vector.h"
#include "fieldInfo.h"
#include "intvector.h"
#include "number.h"
#include <stdio.h>
#include <stdlib.h>


//будем производить вычисления в целых числах
//результат домножается на 10
//в разряд единиц пишется код операции

//КОп 1
void* sumUpTest(const void *arg1, const void *arg2, void *result)
{
    int* first = (int*) arg1;
    int* second = (int*) arg2;
    *((int*) result) = (*first + *second) * 10 + 1;
    return result;
}

//КОп 2
void* multiplyTest(const void* arg1, const void* arg2, void* result)
{
    int* first = (int*) arg1;
    int* second = (int*) arg2;
    *((int*) result) = *first * *second * 10 + 2;
    return result;
}

void* setToZeroTest(void* arg)
{
    *((int*) arg) = 0;
    return arg;
}

void* getElementTest(const void* elements, int index)
{
    int* element = ((int*) elements + index);
    return (void*) element;
}

fieldInfo* getInfoTest()
{
    static fieldInfo* info = NULL;
    if (info == NULL)
    {
        info = malloc(sizeof(fieldInfo));
        if (info == NULL)
        {
            printf("allocation error\n");
            exit(-1);
        }
        info->elementSize = sizeof(int);
        info->sumUp = sumUpTest;
        info->multiply = multiplyTest;
        info->getElement = getElementTest;
        info->setToZero = setToZeroTest;
        info->additional = 't';
    }
    return info;
}


//Функции для тестирования

int compareVectors(vector* a, vector* b)
{
    int result = 1;
    if (getAdditionalData(a) != getAdditionalData(b)) result = 0;
    if (getSize(a) != getSize(b)) result = 0;
    if (result == 0) return result;

    for (int i = 0; i < getSize(a); i++)
    {
        void* arg1 = getInfo(a)->getElement(getElements(a), i);
        void* arg2 = getInfo(a)->getElement(getElements(b), i);
        if (getAdditionalData(a) == 'i' || getAdditionalData(a) == 't')
        {
            if (*((int*) arg1) != *((int*) arg2)) result = 0;
        }
        else if (getAdditionalData(a) == 'r')
        {
            if (*((float*) arg1) != *((float*) arg2)) result = 0;
        }
        else
        {
            result = 0;
        }
    }
    return result;
}

vector* readVectorFromFile(FILE* file, fieldInfo* info)
{
    char* variable = (char*) malloc(sizeof(char)*sizeOfStr);
    if (variable == NULL)
    {
        printf("in readVectorFromFile allocation error\n");
        exit(-1);
    }
    fgets(variable, sizeOfStr, file);
    int dimension = (int) strtol(variable, NULL, radix);
    vector* v = createNewVector(&dimension, info);
    void* elements = getElements(v);
    for (int i = 0; i < dimension; i++)
    {
        fgets(variable, sizeOfStr, file);
        if (variable == NULL)
        {
            printf("in readVectorFromFile reading error\n");
        }
        int a = (int) strtol(variable, NULL, radix);
        *((int*) elements + i) = a;
    }
    free(variable);
    return v;
}

int template(const char* path1, const char* path2, const char* pathAns, int option)
{
    int testRes = 0;
    fieldInfo* info = getInfoTest();
    FILE* arg1 = fopen(path1, "r");
    FILE* arg2 = fopen(path2, "r");
    FILE* answer = fopen(pathAns, "r");
    if (arg1 == NULL || arg2 == NULL || answer == NULL)
    {
        printf("error: null ptr to file\n");
        exit(-1);
    }
    vector* first = readVectorFromFile(arg1, info);
    vector* second = readVectorFromFile(arg2, info);
    vector* vectorExp = readVectorFromFile(answer, info);
    vector* vectorAns;
    switch (option)
    {
    case 1:
        vectorAns = sumUpVectors(first, second);
        break;
    case 2:
        vectorAns = scalarMultiplyVectors(first, second);
        break;
    case 3:
        void* number = getElements(second);
        vectorAns = multiplyByNumber(first, number);
        break;
    default:
        break;
    }
    if (compareVectors(vectorAns, vectorExp) == 1)
    {
        testRes = 1;
    }
    fclose(arg1);
    fclose(arg2);
    fclose(answer);
    freeVector(first);
    freeVector(second);
    freeVector(vectorAns);
    freeVector(vectorExp);
    return testRes;
}

const char* path1 = "./tests/test1/arg1.txt";
const char* path2 =  "./tests/test1/arg2.txt";
const char* pathsum = "./tests/test1/answersum.txt";
const char* pathscal = "./tests/test1/answerscalar.txt";
const char* pathmult = "./tests/test1/answermultiply.txt";

int test1()
{
    int n = 0;
    n += template(path1, path2, pathsum, 1);
    n += template(path1, path2, pathscal, 2);
    n += template(path1, path2, pathmult, 3);
    if (n == 3)
        return 1;
    return 0;
}

void fileTest()
{
    int summary = 0;
    summary += test1();
    printf("in summary: %d tests passed from %d\n", summary, numberOfTests);
    return;
}

int main()
{
    fileTest();
    fieldInfo* info = getInfoTest();
    free(info);
    return 0;
}