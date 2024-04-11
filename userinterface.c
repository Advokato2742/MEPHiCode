#include <stdio.h>
#include <stdlib.h>
#include "FieldInfo.h"
#include "vector.h"
#include "number.h"
#include "userinterface.h"

void UIprintExistigVectors(Vector** list, int* numberOfExistingVectors)
{
    for (int i = 0; i < *numberOfExistingVectors; i++)
    {
        printf("vector %d\n", i+1);
        printf("%d\n", list[i]->size);
        printVector(list[i]);
    }
    return;
}


void UIcreateNewVector(Vector** list, int* numberOfExistingVectors, int option, int dim)
{
    printf("starting creating process for new vector\n");
    Vector** v1 = (Vector**) realloc(list, (*numberOfExistingVectors + 1) * sizeof(Vector*));
    if (v1 == NULL)
    {
        printf("allocating error\n");
        exit(-1);
    }
    list = v1;

    FieldInfo* info = createInfo();
    if (option == 1)
    {
        dim = -1;
        while (dim < 0)
        {
            printf("please enter dimension of space\n");
            printf("dimension cannot be less than 1\n");
            dim = readIntNumb();
        }
    }
    if (dim < 1)
    {
        printf("error receiving information");
        exit(-2);
    }
    Vector* a = info->createNewVector(&dim, info);
    if (option == 1)
    {
        setVector(a);
    }
    list[*numberOfExistingVectors] = a;
    printVector(list[*numberOfExistingVectors]);
    (*numberOfExistingVectors)++;
    return;
}

void UIauxiliaryFunction(Vector** list, int* numberOfExistingVectors, int* first, void* second, int n)
{
    while (*numberOfExistingVectors < n)
    {
        printf("not enough vectors to add up. please add vector\n");
        UIcreateNewVector(list, numberOfExistingVectors, 1, -1);
    }

    while (*first < 0 || *first > *numberOfExistingVectors)
    {
        printf("please select vector numbers from 1 to %d\n", *numberOfExistingVectors);
        *first = readIntNumb();
    }
    if (n == 2)
    {
        while (*((int*) second) < 0 || *((int*) second) > *numberOfExistingVectors)
        {
            printf("please select vector numbers from 1 to %d\n", *numberOfExistingVectors);
            *((int*) second) = readIntNumb();
        }
    }
    else if (n == 1)
    {
        printf("enter the number to multiply by vector\n");
        *((float*) second) = readFloatNumb();
    }

    UIcreateNewVector(list, numberOfExistingVectors, 0, 1);
    return;
}

void UIaddUpVector(Vector** list, int* numberOfExistingVectors)
{
    int first = -1;
    int second = -1;
    UIauxiliaryFunction(list, numberOfExistingVectors, &first, &second, 2);
    Vector* a = ((**list).vInfo)->addUpVector(list[first], list[second]);
    list[*(numberOfExistingVectors - 1)] = a;

    return;
}

void UIscalarMultiply(Vector** list, int* numberOfExistingVectors)
{
    int first = -1;
    int second = -1;
    UIauxiliaryFunction(list, numberOfExistingVectors, &first, &second, 2);
    Vector* a = ((**list).vInfo)->scalarMultiply(list[first], list[second]);
    list[*(numberOfExistingVectors - 1)] = a;
    return;
}

void UImultiplyByNumber(Vector** list, int* numberOfExistingVectors)
{
    int first = -1;
    float second = -1;
    UIauxiliaryFunction(list, numberOfExistingVectors, &first, &second, 1);
    Vector* a = ((**list).vInfo)->multiplyByNumber(list[first], &second);
    list[*(numberOfExistingVectors - 1)] = a;
    return;
}

void UIendOfWork(Vector** list, int* numberOfExistingVectors)
{
    for (int i = 0; i < *numberOfExistingVectors; i++)
    {
        freeVector(*(list + i));
    }
    free(list);
    exit(0);
    return;
}

void userInterface()
{
    int numberOfExistingVectors = 0;
    int error = 0;
    Vector** list = (Vector**) malloc(sizeof(Vector**));
    while (error == 0)
    {
        int option = -1;
        while (option < 1 || option > 6)
        {
            printf("choose option:\n1 - createNewVector\n2 - addUpVector\n3 - scalarMultiply\n");
            printf("4 - multiplyByNumber\n5 - end of work\n6 - print all existing vectors\n");
            option = readIntNumb();
            if (option < 1 || option > 6)
            {
                printf("the option number must be a number from 1 to 6\n");
            }
        }
        switch (option)
        {
        case 1:
            UIcreateNewVector(list, &numberOfExistingVectors, 1, -1);
            break;
        case 2:
            UIaddUpVector(list, &numberOfExistingVectors);
            break;
        case 3:
            UIscalarMultiply(list, &numberOfExistingVectors);
            break;
        case 4:
            UImultiplyByNumber(list, &numberOfExistingVectors);
            break;
        case 5:
            UIendOfWork(list, &numberOfExistingVectors);
            break;
        case 6:
            UIprintExistigVectors(list, &numberOfExistingVectors);
            break;
        }
    }
    return;
}