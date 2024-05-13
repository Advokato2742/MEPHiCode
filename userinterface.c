#include "userinterface.h"
#include "vector.h"
#include "intvector.h"
#include "realvector.h"
#include "number.h"
#include <stdio.h>
#include <stdlib.h>

void UImain()
{
    int option = -1;
    fieldInfo* info;
    while (option != 1 && option != 2)
    {
        printf("select data option. to work with integer coefficients, enter 1. to work with real coefficients, enter 2.\n");
        option = readIntNumb();
    }
    if (option == 1)
    {
        info = getInfoInt();
    }
    else
    {
        info = getInfoReal();
    }
    option = -1;
    while (option < 1 || option > 3)
    {
        printf("Select an action.\n1 - sum up two vectors\n2 - scalar multiply two vectors\n3 - multiply vector by a number\n");
        option = readIntNumb();
    }
    printf("starting process\n");
    int dimension = -1;
    while (dimension < 1)
    {
        printf("enter the quantity of vector coefficients. cannot be less than 1\n");
        dimension = readIntNumb();
    }
    vector* a = createNewVector(&dimension, info);
    enterCoefficient(getSize(a), getElements(a), getAdditionalData(a));
    printVector(a);
    vector* b;
    vector* c;
    void* multiplyer;
    if (option == 3)
    {
        if (info->additional == 'i')
        {
            printf("enter an integer number\n");
            int number = readIntNumb();
            multiplyer = (void*) &number;
        }
        else
        {
            printf("enter a float number\n");
            float number = readFloatNumb();
            multiplyer = (void*) &number;
        }
    }
    else
    {
        dimension = -1;
        printf("for second vector\n");
        while (dimension < 1)
        {
            printf("enter the quantity of vector coefficients. cannot be less than 1\n");
            dimension = readIntNumb();
        }
        b = createNewVector(&dimension, info);
        enterCoefficient(getSize(b), getElements(b), getAdditionalData(b));
    }
    switch (option)
    {
    case 1:
        c = sumUpVectors(a, b);
        freeVector(b);
        break;
    case 2:
        c = scalarMultiplyVectors(a, b);
        freeVector(b);
        break;
    case 3:
        c = multiplyByNumber(a, multiplyer);
        break;
    default:
        break;
    }
    printVector(c);
    freeVector(a);
    freeVector(c);
    free(info);
    return;
}

void UIlaunch()
{
    printf("laboratory work on the subject \"polymorphic and abstract data types\"\n");
    printf("created by Abaidulina V. B23-554\n");
    UImain();
    return;
}