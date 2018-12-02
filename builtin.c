#include "unistd.h"
#include "stdio.h"
#include "sys/types.h"
#include "pwd.h"
#include "stdlib.h"
#include "string.h"
#include "sys/utsname.h"

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
int addaLs(int, char**);
void addaPinfo(char **, int);

int addaCd (int argc, char** args) {
	int flag=0;
	if (strcmp(args[1], "~")==0 || argc==1){
		chdir(home);
	}
	else{
		int first = chdir(args[1]);
		 //on success 0 is returned
		if (first<flag){
			perror("Cd: Error");
		}
	}
	return flag;
}

int addaPwd (int argc, char** args) {
	printf("%s",pwd);
	printf("\n");

	return 0;
}

int addaEcho (int argc, char** args) {
	int num=argc;
	int flag=0;
	for (int i = 1; i < num; i+=1)  {
		printf("%s", args[i]);
	}
	printf("\n");
	return flag;
}



int addaExecute(int argc, char **args, int bgflag) {

	if (strcmp(args[0], "cd")==0) {
    	addaCd(argc, args);
    } 
    else if (strcmp(args[0], "pwd")==0) {
    	addaPwd(argc ,args);
	} 
	else if (strcmp(args[0], "echo")==0) {
	    addaEcho(argc, args); 
	}
  	else if(strcmp(args[0], "pinfo")==0) {
    	addaPinfo(args, argc);
  	}
   	else if(strcmp(args[0], "ls")==0 || strcmp(args[0], "l")==0) {
    	addaLs(argc, args);
	}
  	else {
    return addaProc(args, bgflag);
  }
  return 1;
}
