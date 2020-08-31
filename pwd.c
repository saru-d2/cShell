#include "header.h"

void pwd(){
    char cwd[100000];
    getcwd(cwd, sizeof(cwd));
    printf("%s\n", cwd);
    return;
}