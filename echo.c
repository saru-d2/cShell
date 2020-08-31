#include "header.h"

void echo(char *par[], int numPar){
    char str[100000];
    strcpy(str, "");
    for(int i =0; i<numPar; i++){
        strcat(str, par[i]);
        strcat(str, " ");
    }
    int slen = strlen(str);
    int ind = 1;
    if (str[0] == '"' && str[slen - 2]== '"'){
        for (; ind<slen -1; ind++)
            str[ind-1] = str[ind];
        str[ind -2] = '\0';
    }
    printf("%s\n", str);
}