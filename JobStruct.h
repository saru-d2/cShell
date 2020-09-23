typedef struct job
{
    pid_t id;
    char name[1000];
    bool running;
} job;