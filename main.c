#include <stdio.h>
#include <stdlib.h>
#include "FieldInfo.h"
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
    FieldInfo* info = infoInt;
    VectorInt* a;
    int d = 3;
    a = createNewVectorInt(&d, infoReal);
    VectorReal* b;
    printVectorInt(a);
    /*
    
    VectorInt* b;
    VectorInt* c;
    int lena = readIntNumb(), lenb = readIntNumb(), lenc = readIntNumb();
    a = createNewVectorInt(&lena, infoInt);
    b = createNewVectorInt(&lenb, infoInt);
    c = createNewVectorInt(&lenc, infoInt);
    setVectorInt(a);
    setVectorInt(b);
    setVectorInt(c);
    int numb = 3;
    VectorInt* sumac = infoInt->addUpVector(a, c);
    VectorInt* pAC = infoInt->scalarMultiply(a, c);
    VectorInt* bup = infoInt->multiplyByNumber(b, &numb);
    printVectorInt(sumac);
    printVectorInt(pAC);
    printVectorInt(bup);
    freeVectorInt(a);
    freeVectorInt(bup);
    freeVectorInt(b);
    freeVectorInt(c);
    freeVectorInt(sumac);
    freeVectorInt(pAC);
    */
    freeVectorInt(a);
    printf("3\n");
    //freeVectorReal(b);
    printf("2\n");
    free(infoInt);
    printf("1\n");
    free(infoReal);
    printf("exit");
    return 0;
}