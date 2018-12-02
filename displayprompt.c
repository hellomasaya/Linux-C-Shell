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

char* display() {
    /********** UID of user **********/
    int uid = getuid();
	/********** user info through password ***********/
	struct passwd *currentUser = getpwuid(uid);
	/********** user name ***********/
	char *username = currentUser -> pw_name;
	/********** host name ***********/  
	struct utsname sysinfo;
  	
	// gethostname(sysinfo.nodename, 30);
	if (uname(&sysinfo) != 0) {
    	perror("uname");
    	// exit(EXIT_FAILURE);
    }

	char hostname[31];
    strcpy(hostname, sysinfo.nodename); //or strcpy
    char store[1000];
	char new_store[2000];
char store2[1000];
	int zero=0;
	sprintf(store, "\e[37m<\e[32;1m%s\e[39m@\e[34;1m%s\e[39m:\e[95m",username, hostname);

	/********************************************
	 *******Current working directory ***********
	*******************************************/
	getcwd(pwd, sizeof(pwd));
	if (strcmp(pwd, home) == zero){
		strcat(store, "~>\e[39m");
	}
	else {

		if (strlen(pwd) > strlen(home))
		{
			if( strncmp(pwd, home, strlen(home)) == zero){
			sprintf(store2, "~%s>\e[39m",pwd + strlen(home));
			strcat(store, store2);
			}
		}
		else{
			sprintf(store2, "%s>\e[39m", pwd);
			strcat(store, store2);
		}
	}
	printf("%s", store);
	strcpy(prompt, store);
	return prompt;
}
