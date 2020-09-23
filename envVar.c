#include "header.h"

void unSetVar(int numPar, char *par[])
{
    if (numPar != 1){
        fprintf(stderr, "WRONG NO OF ARGUMENTS\n");
        exit(0);
    }
    if (unsetenv(par[0]) < 0){
        perror("unsetenv");
    }
}

void setVar(int numPar, char *par[])
{
    if (numPar != 2){
        fprintf(stderr, "WRONG NO OF ARGUMENTS\n");
        exit(0);
    }
    if (setenv(par[0],par[1],1) < 0){
        perror("setenv");
    }
}