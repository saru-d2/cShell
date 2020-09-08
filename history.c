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
        cmdLine = strtok(temp->cmd, "\n");
        strcat(cmdLine, "\n");
        write(fd, cmdLine, strlen(cmdLine));
        temp = temp->next;
    }
}

void pushHisQ(char st[])
{
    historyNode *temp = (historyNode *)malloc(sizeof(historyNode));
    temp->next = NULL;
    temp->prev = NULL;
    strcpy(temp->cmd, st);
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
    int fd = open("./history.txt", O_RDONLY, O_CREAT);
    char cmd[1000];
    if (fd < 0)
    {
        perror("History File: ");
        return;
    }
    char buffer[1000];
    read(fd, buffer, 1000);
    // while (fgets(cmd, 1000, hisFile) != NULL)
    // {
    //     if (strcmp(cmdLine, "") == 0)
    //         continue;
    //     cmdLine = strtok(cmd, "\n");
    //     puts(cmdLine);
    //     pushHisQ(cmdLine);
    // }
    char *hisLines[20];
    hisLines[0] = strtok(buffer, "\n");
    int i =0;
    while(hisLines[i] != NULL){
        puts(hisLines[i]);
        pushHisQ(hisLines[i]);
        hisLines[++i] = strtok(NULL, "\n");
    }
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
    historyNode *temp = head;
    int i = 0;
    while (temp != NULL && i < size)
    {
        if (size - i <= num)
            printf("%s\n", strtok(temp->cmd, "\n"));
        temp = temp->next;
        i++;
    }
}