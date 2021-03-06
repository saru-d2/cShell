#include "header.h"
#include "JobStruct.h"

int kjob(int numPar, char *par[], job jobArr[], int *jobIterPtr, bool *kjobFlagptr)
{
    if (numPar != 2)
    {
        printf("wrong no. of arguments\n");
        return -1;
    }
    int it = *jobIterPtr;
    int num = atoi(par[0]);
    int sig = atoi(par[1]);
    num--;

    printf("%d\n", jobArr[num].id);

    if (it < num || num < 0)
    {
        printf("wrong number for arg1\n");
        return -1;
    }
    else
    {

        if (jobArr[num].running)
        {
            if (sig == 9)
            {
                *kjobFlagptr = false;
                // printf("wow much 9\n");
            }
            kill(jobArr[num].id, sig);
        }
        else
        {
            printf("it wasnt running\n");
            return -1;
        }
    }
    return 1;
}