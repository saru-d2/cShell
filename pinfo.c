#include "header.h"

int strToNum(char s[])
{
    int ret = 0;
    for (int i = 0; s[i] != '\0'; i++)
    {
        ret *= 10;
        ret += s[i] - '0';
    }
    return ret;
}

void pinfo(char *par[], int numPar)
{
    int ID;
    if (numPar == 0)
    {
        numPar = 1;
        ID = getpid();
    }
    else
    {
        if (numPar > 1)
        {
            perror("pinfo: Too many arguments!");
            return;
        }
        ID = strToNum(par[0]);
    }
    char procFile[10000];
    sprintf(procFile, "/proc/%d/stat", ID);
    FILE *fd = fopen(procFile, "r");
    if (fd == NULL)
    {
        perror("Can't seem to find respective pid deirectory in proc");
        return;
    }
    printf("pid -- %d\n", ID);
    char buffer[10000];
    for (int i = 0; fscanf(fd, "%s", buffer); i++)
    {
        if (i == 2)
            printf("Process Status -- %s\n", buffer);
        if (i == 21)
            printf("memory -- %s\n", buffer);
    }

    return;
}