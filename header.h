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
int cd();
void cdInit();
int pwd();
int echo();
int ls();
void assignPermissions();
int foregnd();
int backgnd();
int clear();
int pinfo();
int strToNum();
void bgProcessEnd();
void historyInit();
int printHis();
void pushHisQ();
void updateHistory();
int nightswatch();
int newBorn();
int interr();
int execCmd();
int jobs();
bool pipeChk();
int Pipe();
int unSetVar();
int setVar();
int kjob();
void getshPid();
void setChPid();
void ctrlCZinit();
void addToJobArr();
int overkill();
int killall();
int bg();
int fg();
void quit();
void overKillFlagTrue();