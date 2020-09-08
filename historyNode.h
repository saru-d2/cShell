typedef struct historyNode
{
    struct historyNode *next;
    struct historyNode *prev;
    char cmd[1000];
    
}historyNode;