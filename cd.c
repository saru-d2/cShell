#include "header.h"

void cd(int numPar, char *par[], char home_dir[])
{
    if (numPar > 1){
        perror("Too many arguments");
        return;
    };
    if (numPar == 0){
        chdir(home_dir);
        return;
    }
    char path[100000], temp[100000];
    strcpy(path, par[0]);
    printf("%s\n", path);
    if (path[0] == '~'){
        strcpy(temp, home_dir);
        int pathln = strlen(path);
        int homeln = strlen(home_dir);
        for (int i =1; i<pathln; i++){
            temp[homeln+i-1] = path[i];
        }
        temp[homeln + pathln -1] = '\0';
        printf("%s\n", temp);
        strcpy(path, temp);
        int valid = chdir(path);
        if (valid < 0){
            perror("No such path/ directory");
        }
        return;
    }
    int valid = chdir(path);
    if (valid < 0){
        perror("No such path/ directory");
    }
}