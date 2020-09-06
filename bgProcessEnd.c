#include "header.h"
#include "JobStruct.h"

void bgProcessEnd(job jobArr[], int jobIter, char *home_dir){
    pid_t pid;
    int stat;
    pid = waitpid(-1, &stat, 1);
    if (pid < 0){
        perror("Error: waitPid returned negative value");
        return;
    }
    printf("\n");
    printf("pid: %d\n", pid);
    printf("%d ", jobIter);
    for (int i = 0; i < jobIter; i++)
    {
        printf("qwqw%d \n", jobArr[jobIter].id);
        if (jobArr[jobIter].id == pid){
            printf("%s\n", jobArr[jobIter].name);
        }
    }
    print_PS1(home_dir);
    fflush(NULL);
    return;
}