typedef struct historyNode
{
    struct historyNode *next;
    struct historyNode *prev;
    char hisLine[1000];
    
}historyNode;