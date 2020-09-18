#include "header.h"
#include "JobStruct.h"
char *cmd, *breaks[1000], *par[1000];

bool Pipe(char *line, char *home_dir, job jobArr[], int *jobIterPtr)
{
    
    int numPipeSep = 0;
    char *pipeSep[1000];
    pipeSep[0] = strtok(line, "|");
    while (line != NULL)
    {
        pipeSep[numPipeSep++] = line;
        line = strtok(NULL, "|");
    }
    int oldStdin = dup(STDIN_FILENO);
    int oldStdout = dup(STDOUT_FILENO);
    // printf("%d\n", numPipeSep);
    for (int i = 0; i < numPipeSep - 1; i++)
    {
        int pipeFd[2];
        //pipe creation
        if (pipe(pipeFd) < 0)
        {
            perror("pipe");
            return true;
        }

        int fdIn = pipeFd[0];
        int fdOut = pipeFd[1];

    }
    return true;
}