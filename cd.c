#include "header.h"
char prev[1000];

int cd(int numPar, char *par[], char home_dir[])
{
    if (numPar > 1)
    {
        perror("Too many arguments");
        return -1 ;
    };
    if (numPar == 0)
    {
        int ret = chdir(home_dir);
        return ret;
    }
    char path[100000], temp[100000];
    strcpy(path, par[0]);
    // printf("%s\n", path);
    if (path[0] == '~')
    {
        strcpy(temp, home_dir);
        int pathln = strlen(path);
        int homeln = strlen(home_dir);
        for (int i = 1; i < pathln; i++)
        {
            temp[homeln + i - 1] = path[i];
        }
        temp[homeln + pathln - 1] = '\0';
        // printf("%s\n", temp);
        strcpy(path, temp);
        int valid = chdir(path);
        if (valid < 0)
        {
            perror("cd");
            return -1;
        }
        return 1;
    }
    if (strcmp("-", par[0]) == 0)
    {
        strcpy(path, prev);
        printf("%s\n", path);
    }
    getcwd(prev, sizeof(prev));
    int valid = chdir(path);
    if (valid < 0)
    {
        perror("cd");
        return -1;
    }
    return 1;
}

void cdInit(char homeDir[])
{
    strcpy(prev, homeDir);
}