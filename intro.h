#include "unistd.h"
#include "stdio.h"
#include "sys/types.h"
#include "pwd.h"
#include "stdlib.h"
#include "string.h"
#include "sys/utsname.h"
#include "signal.h"
#include <sys/types.h>
#include <sys/wait.h>

char home[1000];  
char* commands[20];
char prompt[1000];
char pwd[1000]; 

char* display();
int readInput();
char** splitTokens(char* );
int addaCd (int, char**);
int addaPwd (int, char**);
int addaEcho (int, char**);
int addaExecute(int, char**, int);
int addaCheck(char**);
int addaProc(char**, int);

