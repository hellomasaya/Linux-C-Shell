#include "unistd.h"
#include "stdio.h"
#include "sys/types.h"
#include "pwd.h"
#include "string.h"
#include "sys/utsname.h"
#include "stdlib.h"



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

int readInput(){
	char *input = display();

  	ssize_t size = 0;
  	getline(&input, &size, stdin);

	if (input == NULL){
		printf("\n");
		return 0;
	}


	const char delimeter[2] = ";";
	int count = 0;
	commands[0] = strtok(input, delimeter); // Breaking line into commands

	while(commands[count] != NULL ){
		commands[++count] = strtok(NULL, delimeter);
	}
	// storing number of commands 
	int ans=count;
	//number of commands is the answer 
	return ans; 
}

char** splitTokens(char* command){

	ssize_t bufsize = 50;
	int temp=0,flag=0,tok=0;
	char **tokens = malloc(bufsize * sizeof(char*)), **temp_tokens;
	int flag2=1;
	if(!tokens){
		fprintf(stderr, "SHELL: Memory Allocation Error");
		exit(3);
	}
	tokens[temp] = strtok(command, " \t\r\n\a");    

	while(tokens[temp] != NULL){
		tok=0;
		tokens[++temp] = strtok(NULL, " \t\r\n\a");

		if (bufsize <= temp){
			bufsize += 50;
			flag=1;
			temp_tokens = tokens;
			tok=1;
			tokens = realloc(tokens, bufsize * sizeof(char*));
			if (!tokens && flag2) {
				free(temp_tokens);
				fprintf(stderr, "SHELL: Memory Allocation Error");
				exit(3);
			}
		}
	}
	
	tokens[temp] = NULL;
	return tokens;
}
