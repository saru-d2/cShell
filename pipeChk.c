#include "header.h"
char temp[1000];
bool pipeChk(char *cmdLine){
    strcpy(temp, cmdLine);
    char *sep;
    sep = strtok(temp, " \t\r\n");
    while(sep != NULL){
        if (sep[strlen(sep) - 1] == '|')
            return true;
        sep = strtok(NULL, "\t\r\n");
    }
    return false;
}