#include "header.h"
char temp[1000];
bool pipeChk(char *cmdLine)
{
    for (int i = 0; i < strlen(cmdLine); i++)
    {
        if (cmdLine[i] == '|')
            return true;
    }
    return false;
}