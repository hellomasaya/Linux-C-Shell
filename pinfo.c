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
#include "fcntl.h"
#include <sys/stat.h>

char home[1000];  
char* commands[20];
char prompt[1000];
char pwd[1000]; 
int bgcount;

char* display();
int readInput();
char** splitTokens(char* );
int addaCd (int, char**);
int addaPwd (int, char**);
int addaEcho (int, char**);
int addaExecute(char**, int);
int addaCheck(char**);
int addaProc(char**, int);

void addaPinfo(char **args, int argc){
  char pid[10];
  if(argc > 1){ // if we know the pid
    strcpy(pid, args[1]);
  }
  else{ // else pinfo self
    sprintf(pid, "%d", getpid());
  }

  char procpath[1024];
 
  strcpy(procpath, "/proc/");
  strcat(procpath, pid);

  char statpath[1024];
 
  strcpy(statpath, procpath);

  strcat(procpath, "/stat");
  strcat(statpath, "/exe");
  
  char exepath[1024];

  int t = readlink(statpath, exepath, sizeof(exepath));
  if(t == -1){
    strcpy(exepath, "broken link");
  }
  exepath[t] = '\0';

  char relpath[1024];
  int zero=0;
  if (strlen(exepath) > strlen(home) && strncmp(pwd, home, strlen(home)) == zero){
    strcpy(relpath, "~");
    strcat(relpath, exepath + strlen(home));
  }
  else{
    strcpy(relpath, exepath);
  }
 
  int FileD = open(procpath, O_RDONLY);
  if(FileD == -1){
    perror("Error");
    return;
  }
  char name[3000];
  read(FileD, name, 250);

  char **stat;

  stat = splitTokens(name);
  printf("pinfo\n");
  printf("pid -- %s\nProcess Status -- %s\nVirtual Memory-- %s\nExecutable Path -- %s\n", stat[0], stat[2], stat[23], exepath);
}
