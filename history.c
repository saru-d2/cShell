#include "header.h"
#include "historyNode.h"

historyNode *head = NULL, *tail = NULL;

int size = 0;

void updateHistory()
{
    // printf("updating");
    historyNode *temp = head;
    int fd = open("./history.txt", O_WRONLY | O_CREAT);
    char *cmdLine;
    while (temp != NULL)
    {
        // printf("%s\n", temp->cmd);
        cmdLine = strtok(temp->hisLine, "\n");
        strcat(cmdLine, "\n");
        write(fd, cmdLine, strlen(cmdLine));
        temp = temp->next;
    }
    
}

void pushHisQ(char st[])
{
    // printf("%s\n", st);
    historyNode *temp = (historyNode *)malloc(sizeof(historyNode));
    temp->next = NULL;
    temp->prev = NULL;
    strcpy(temp->hisLine, st);
    size++;
    if (head == NULL)
    {
        head = temp;
        tail = temp;
    }
    else
    {
        temp->prev = tail;
        tail->next = temp;
        tail = temp;
    }
    while (size > 10)
    {
        head = head->next;
        head->prev = NULL;
        size -= 1;
    }
    updateHistory();
}

void historyInit()
{
    FILE *hisFile = fopen("./history.txt", "rw");
    char cmd[1000];
    if (hisFile == NULL)
    {
        perror("History File: ");
        printf("creating and changing permissions of file\n");
        chmod("./history.txt", 0777);
        return;
    }
    char *cmdLine;
    while (fgets(cmd, 1000, hisFile) != NULL)
    {
        cmdLine = strtok(cmd, "\n");
        if (cmdLine == NULL)
        {
            continue;
        }
        pushHisQ(cmdLine);
    }
    fclose(hisFile);
    updateHistory();
}

void printHis(int numPar, char *par[])
{
    if (numPar > 1)
    {
        perror("history: Too many arguments:");
        return;
    }
    int num = 10;
    if (numPar == 1)
    {
        num = atoi(par[0]);
    }
    if (num > size)num = size;
    historyNode *temp = head;
    int i = 0;
    while (temp != NULL && i < size)
    {
        if (size - i <= num)
            printf("%s\n", strtok(temp->hisLine, "\n"));
        temp = temp->next;
        i++;
    }
}