#include <stdio.h>
#include "number.h"

int readIntNumb(){
    int t, err = -1;
    while (err < 1){
        err = scanf("%d", &t);
        scanf("%*[^\n]");
        if (err == -1){
            printf("EOF\nPlease enter an integer\n");
        }
        else if (err == 0){
            printf("alphabet\nPlease enter an integer\n");
        }
        else{
            printf("integer read\n");
        }
    }
    return t;
}
float readFloatNumb(){
    float t;
    int err = -1;
    while (err < 1){
        err = scanf("%f", &t);
        scanf("%*[^\n]");
        if (err == -1){
            printf("EOF\n");
            return err;
        }
        else if (err == 0){
            printf("alphabet\nPlease enter a number");
        }
        else{
            printf("all right\n");
        }
    }
    return t;
}
