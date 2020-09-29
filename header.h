//header files...
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/stat.h>
#include <stdbool.h>
#include <pwd.h>
#include <fcntl.h>
#include <time.h>
#include <grp.h>
#include <dirent.h>
#include <stdlib.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <sys/select.h>

//colors
#define TANGO_RED "\033[0;31m"
#define TANGO_GREEN "\033[0;32m"
#define TANGO_YELLOW "\033[0;33m"
#define TANGO_BLUE "\033[0;34m"
#define TANGO_PURPLE "\033[0;35m"
#define TANGO_CYAN "\033[0;36m"
#define TANGO_WHITE "\033[0m"

//functions
void loop();      //main loop..
void print_PS1(); //print the PS1..
void cd();
void pwd();
void echo();
void ls();
void assignPermissions();
void foregnd();
void backgnd();
void clear();
void pinfo();
int strToNum();
void bgProcessEnd();
void historyInit();
void printHis();
void pushHisQ();
void updateHistory();
void nightswatch();
void newBorn();
void interr();
bool execCmd();
void jobs();
bool pipeChk();
bool Pipe();
void unSetVar();
void setVar();
void kjob();
void getshPid();
void setChPid();
void ctrlCZinit();
void addToJobArr();
void overkill();
void killall();
void bg();
void fg();