#include "header.h"

int echo(char *par[], int numPar){
    char str[100000];
    strcpy(str, "");
    for(int i =0; i<numPar; i++){
        strcat(str, par[i]);
        strcat(str, " ");
    }
    printf("%s\n", str);
    return 1;
}