#include <stdio.h>
#include <stdlib.h>
#include "fieldInfo.h"
#include "intvector.h"
#include "number.h"
#include "realvector.h"
#include "userinterface.h"

FieldInfo* infoInt;
FieldInfo* infoReal;

int main()
{
    infoInt = createInfoInt();
    infoReal = createInfoReal();
    userInterface();
    free(infoInt);
    free(infoReal);
    return 0;
}