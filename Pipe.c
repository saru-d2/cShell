#include "header.h"
#include "JobStruct.h"

int Pipe(char *line, char *home_dir, job jobArr[], int *jobIterPtr, bool *kjobFlag)
{
    int exRet;
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

    // creating all pipes
    int fdPipe[(numPipeSep + 1) * 2];
    for (int i = 0; i < numPipeSep; i++)
    {
        int pret = pipe(fdPipe + i * 2);
        if (pret < 0)
        {
            perror("pipe not formed");
            exit(0);
        }
    }
    int dup2Ret;
    for (int i = 0; i < numPipeSep; i++)
    {

        if (i > 0)
        {
            // write(2, pipeSep[i], strlen(pipeSep[i]));
            // write(2, "??\n", strlen("??\n"));
            dup2Ret = dup2(fdPipe[2 * (i - 1)], STDIN_FILENO);
            if (dup2Ret < 0)
            {
                perror("pipe, dup2 failed");
                exit(0);
                
            }
            close(fdPipe[2 * (i - 1)]);
        }

        if (i < numPipeSep - 1)
        {
            // write(2, pipeSep[i], strlen(pipeSep[i]));
            // write(2, "!!\n", strlen("!!\n"));
            dup2Ret = dup2(fdPipe[(2 * i) + 1], STDOUT_FILENO);
            if (dup2Ret < 0)
            {
                perror("pipe, dup2 failed");
                exit(0);
            }
            close(fdPipe[(2 * i) + 1]);
        }
        exRet = execCmd(pipeSep[i], home_dir, jobArr, jobIterPtr, kjobFlag);
        // fprintf(stderr, "done %d\n", exRet);
        fflush(NULL);
        dup2(oldStdin, STDIN_FILENO);
        dup2(oldStdout, STDOUT_FILENO);
    }
    int stat;
    // printf("!!%d!!\n", exRet);
    return exRet;
}