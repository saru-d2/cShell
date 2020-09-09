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

void pinfo(char *par[], int numPar, char home_dir[])
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
        perror("pinfo: /proc/../stat");
        return;
    }
    printf("pid -- %d\n", ID);
    char infoStr[10000];
    for (int i = 0; fscanf(fd, "%s", infoStr); i++)
    {
        if (i == 23)break;
        if (i == 2)
            printf("Process Status -- %s\n", infoStr);
        if (i == 21)
            printf("memory -- %s\n", infoStr);
    }
    sprintf(procFile, "/proc/%d/exe", ID);
    int n = readlink(procFile, infoStr, 10000);
    if (n <= -1)
    {
        perror("error reading executable path");
        return;
    }
    infoStr[n] = '\0';
    int hlen = strlen(home_dir);
    bool rel = true;
    if (n < hlen)
        rel = false;
    if (rel)
        for (int i = 0; i < hlen; i++)
        {
            if (home_dir[i] != infoStr[i])
                rel = false;
        }
    char fin[100000];
    if (!rel){
        strcpy(fin, infoStr);
    }
    else {
        strcpy(fin, "~");
        strcat(fin, infoStr + hlen);
    }
    printf("Executable path -- %s\n", fin);
    return;
}