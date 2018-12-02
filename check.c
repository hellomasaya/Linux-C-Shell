#include "unistd.h"
#include "stdio.h"
#include "sys/types.h"
#include "pwd.h"
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
int addaCheck(char**);
int addaExecute(int, char**, int);


int addaCheck(char **args){
	int bgflag=0;
	int redirect=0;
	int pipe=0;
	int argc = 0; // Number of Arguments

	while (args[argc] != NULL){
		if (strcmp(args[argc], "<")==0 || strcmp(args[argc], ">")==0 || strcmp(args[argc], ">>")==0 ){
			redirect = argc;
		}
		argc++;
	}

	if (argc == 0){
		printf("\n");
		return 1;
	}

	if (strcmp(args[argc - 1], "&")==0){
		bgflag = 1;
		argc--;
		args[argc] = NULL; 
	}

	return addaExecute(argc, args, bgflag);

}
