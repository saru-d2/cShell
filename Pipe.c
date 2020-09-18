#include "header.h"
#include "JobStruct.h"
char *cmd, *breaks[1000], *par[1000];

bool execCmd(char *line)
{
    // write(2, line,strlen(line));
    // write(2, "!\n!", strlen("!\n!"));
    
    return true;
}

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
    printf("%d\n", numPipeSep);
    for (int i = 0; i < numPipeSep; i++)
    {
        int pipeFd[2];
        //pipe creation
        if (pipe(pipeFd) < 0)
        {
            perror("pipe");
            return true;
        }
        if (i != 0)
            dup2(pipeFd[0], STDIN_FILENO);
        if (i != numPipeSep - 1)
            dup2(pipeFd[1], STDOUT_FILENO);

        execCmd(pipeSep[i]);
        
    }

    dup2(oldStdin, STDIN_FILENO);
    dup2(oldStdin, STDOUT_FILENO);
    return true;
}