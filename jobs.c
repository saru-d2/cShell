#include "header.h"
#include "JobStruct.h"

void jobs(int numPar, char *par[], job jobArr[], int *jobIterPtr){
    int jobCnt = *jobIterPtr;
    for (int i =0; i<jobCnt; i++){
        int pid = jobArr[i].id;
        char procFile[1000];
        sprintf(procFile, "/proc/%d/stat", pid);
        FILE *fd = fopen(procFile, "r");
        if (fd == NULL){
            perror("jobs, read proc/../stat");
            exit(0);
        }
        char infoStr[1000];
        for (int i = 0; fscanf(fd, "%s", infoStr); i++)
        {
            if (i == 3)
                break;
            if (i == 2)
                printf("Process Status -- %s\n", infoStr);
        }

        
    }
}