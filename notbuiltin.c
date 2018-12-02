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


void exited(int sig){

	pid_t wpid;
	int status;
	wpid=wait(NULL);

	if(wpid > 0 && WIFEXITED(status)==0){
		printf("\nProcess with pid %d exited normally\n", wpid);
		bgcount--;
	}
	if(wpid > 0 && WIFSIGNALED(status)==0){
		printf("\nProcess with pid %d exited due to a user-defined signal\n", wpid);
	}
}
int addaProc(char **args, int bgflag){
	
	pid_t pid;
	int status;
	int bg_count=0;
	signal(SIGCHLD, exited);
	
	pid = fork();

	if (pid < 0) {
		perror("shell: Error, cant create fork");
	}
	else if (pid == 0){

		if(bgflag){
			setpgid(0, 0);
		}
		int temp = execvp(args[0], args);

		if (temp == -1) {
			perror("shell: Error Executing >");
		}
		exit(1);

	}

	if (!bgflag){
			do {
				waitpid(pid, &status, WUNTRACED);
			} while (!WIFEXITED(status) && !WIFSIGNALED(status));
		}
		else{ // Background process
			waitpid(-1, &status, WNOHANG);
			bg_count++;
		}

	return 1;
}