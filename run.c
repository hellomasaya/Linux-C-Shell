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
int addaExecute(int, char**, int);
int addaCheck(char**);


int main(int argc, char const *argv[]){
	
	int status=1;
	getcwd(home, sizeof(home));
	int number_of_cmds;
	char **args;
	do {
		number_of_cmds = readInput();
		int i=0;
		for (i = 0; i < number_of_cmds; i++){
			args = splitTokens(commands[i]);
			status = addaCheck(args);
		}
	} while(status);
	return 0;
}
