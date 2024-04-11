#pragma once
#include "vector.h"

void userInterface(void);
//list = "begin of list"
//int* for count of vectors in list
//option = 1 - hand set, option = 0 - auto set
//dim = -1 with option 1 and dim = "your dimention" with option = 0
void UIcreateNewVector(Vector**, int*, int, int);
//list = "begin of list"
//int* for count of vectors in list
//int* first for index of first vector
//int* second - if n = 2 pointer to index of second vector, if n = 1 pointer to real number
//int n = 2 - func create 2 vectors, n = 1 - func create vector and read real number
void UIauxiliaryFunction(Vector**, int*, int*, void*, int);
void UIaddUpVector(Vector**, int*);
void UIscalarMultiply(Vector**, int*);
void UImultiplyByNumber(Vector**, int*);
void UIendOfWork(Vector**, int*);
void UIprintExistigVectors(Vector**, int*);