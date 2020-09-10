#include "header.h"

bool qPressed()
{

    fd_set fd;
    FD_SET(0, &fd);

    struct timeval tVal;
    tVal.tv_sec = 0;
    tVal.tv_usec = 0;

    int selRet = select(1, &fd, NULL, NULL, &tVal);
    if (selRet > 0)
    {
        char c = fgetc(stdin);
        if (c == EOF)
            return false;
        if (c == 'q')
        {
            fgetc(stdin); //for enter
            return true;
        }
    }
    else if (selRet < 0)
    {
        perror("select() for watching if q");
        return true;
    }
    else
    {
        return false;
    }

    return false;
}

void interr(int timeInt)
{
    long noOfThreads = sysconf(_SC_NPROCESSORS_ONLN);
    char buffer[1000];
    for (int i = 0; i < noOfThreads; i++)
        printf("CPU%d\t", i);
    printf("\n");
    char *itups[noOfThreads + 5];
    int cnt = 0;

    FILE *fd;
    while (true)
    {
        fd = fopen("/proc/interrupts", "r");
        if (fd == NULL)
        {
            perror("nightswatch interrupt: /proc/interrupts");
            break;
        }
        int i = 0;
        while (fgets(buffer, 1000, fd) != NULL && i++ < 3)
        {
            if (i != 3)
                continue;
            if (i == 3)
            {
                // puts(buffer);
                fflush(NULL);
                int j = 0;
                itups[0] = strtok(buffer, " \t\n");
                while (j < noOfThreads)
                {
                    // puts(itups[j]);
                    itups[++j] = strtok(NULL, " \t\n");
                }
            }
            for (int k = 1; k <= noOfThreads; k++)
            {
                printf("%s\t", itups[k]);
            }
            printf("\n");
        }

        if (qPressed())
            return;
        sleep(timeInt);
        if (qPressed())
            return;
    }
    return;
}

void newBorn(int timeInt)
{
    bool run = true;
    int i = 0;
    int pid;
    printf("in newborn\n");
    while (run)
    {
        FILE *fd = fopen("/proc/loadavg", "r");
        if (fd == NULL)
        {
            perror("Nightswatch newborn read /proc/loadavg");
        }
        fscanf(fd, "%*s %*s %*s %*s %d", &pid);
        printf("%d\n", pid);
        if (qPressed())
            break;
        sleep(timeInt);
        if (qPressed())
            break;
        fclose(fd);
    }
}

void nightswatch(int numPar, char *par[])
{
    // printf("timeInt: %d\n", timeInt);
    if (numPar == 3 && strcmp(par[0], "-n") == 0)
    {
        int timeInt = atoi(par[1]);
        if (strcmp(par[2], "interrupt") == 0)
        {
            interr(timeInt);
        }
        else if (strcmp(par[2], "newborn") == 0)
        {
            newBorn(timeInt);
            // printf("ayee\n");
        }
        else
        {
            printf("wrong input\n");
            return;
        }
    }
    else if (numPar == 3)
    {
        printf("Wrong input\n");
    }
    else if (numPar == 1)
    {
        if (strcmp(par[0], "interrupt") == 0)
        {
            interr(1);
        }
        else if (strcmp(par[0], "newborn") == 0)
        {
            newBorn(1);
            // printf("ayee\n");
        }
        else
        {
            printf("wrong input\n");
            return;
        }
    }
}