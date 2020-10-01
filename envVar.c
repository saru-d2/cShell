#include "header.h"

int unSetVar(int numPar, char *par[])
{
    if (numPar != 1){
        fprintf(stderr, "WRONG NO OF ARGUMENTS\n");
        return -1;
    }
    if (unsetenv(par[0]) < 0){
        perror("unsetenv");
        return -1;
    }
    return 1;
}

int setVar(int numPar, char *par[])
{
    if (numPar != 2){
        fprintf(stderr, "WRONG NO OF ARGUMENTS\n");
        return -1;
    }
    if (setenv(par[0],par[1],1) < 0){
        perror("setenv");
        return -1;
    }
    return 1;
    
}