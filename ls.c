#include <dirent.h>
#include "unistd.h"
#include "stdio.h"
#include "sys/types.h"
#include "sys/stat.h"
#include "pwd.h"
#include "string.h"
#include "sys/utsname.h"
#include "dirent.h"
#include "time.h"
#include "pwd.h"
#include "grp.h"

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


int addaLs(int argc, char **args){
  struct dirent *name;
  DIR *curDir;
  struct stat fileStat;

  char fullpath[256];
  int one =1;
  int flag_a = 0;
  int  flag_l = 0;
  int zero=0;
  int  directory = 0, flag_la=0, no_directories=0;

  for (int i = 1; i < argc; i++) {
    if (strcmp(args[i], "-a") == zero)
      flag_a = 1;
    else if (strcmp(args[i], "-l") == zero)
      flag_l = 1;
    else if (strcmp(args[i], "-al") == zero){
      flag_la = 1;
      flag_l=1;
      flag_a=1;
    }
    else if( strcmp(args[i], "-la") == zero)
    {

      flag_la = 1;
      flag_l=1;
      flag_a=1;
    }
	else{
		directory=i; 
	}    

  	}

  no_directories = argc - 1 - flag_a - flag_l - flag_la;
   if(!directory) //only ls is entered
  {
  	args[1]=".";
  	directory=1;
  	no_directories=1;
  }
  //ls -a -l dir1 dir2 
  for(int j=0; j < (no_directories); j++, directory--){
  	curDir = opendir(args[directory]); //directory stream
	if (curDir == NULL){
		printf("%s: No such file or directory\n", args[directory]);
		continue;
	}
	while((name = readdir(curDir)) != NULL){
      if (stat(name->d_name, &fileStat) != 0){
        continue;
      }
      if(name->d_name[0] == '.'){
	      if (!flag_a)  
    	  	continue;
      }
    
      strcpy (fullpath, args[directory]);
	  strcat (fullpath, "/");
	  strcat (fullpath, name->d_name);
      if (!flag_a && !flag_l && name->d_name[0] != '.'){
				// printf("Im working !l!a\n");

        printf("%s\n", name->d_name);
      }
      else if (flag_a && !flag_l) {
				// printf("Im working !l,a\n");

        printf("%s\n", name->d_name);
      }
      else if (flag_l) {
		if (!stat(fullpath, &fileStat)) {
			struct passwd* user = getpwuid(fileStat.st_uid);
				struct group* group = getgrgid(fileStat.st_gid);
				time_t now;
				time(&now);
				int year = localtime(&now)->tm_year;
				struct tm* strtime = localtime(&fileStat.st_ctime);
				unsigned char date[130];
				// printf("Im working -l\n");
				printf((S_ISDIR(fileStat.st_mode))  ? "d" : "-");
				printf((fileStat.st_mode & S_IRUSR) ? "r" : "-");
				printf((fileStat.st_mode & S_IWUSR) ? "w" : "-");
				printf((fileStat.st_mode & S_IXUSR) ? "x" : "-");
				printf((fileStat.st_mode & S_IRGRP) ? "r" : "-");
				printf((fileStat.st_mode & S_IWGRP) ? "w" : "-");
				printf((fileStat.st_mode & S_IXGRP) ? "x" : "-");
				printf((fileStat.st_mode & S_IROTH) ? "r" : "-");
				printf((fileStat.st_mode & S_IWOTH) ? "w" : "-");
				printf((fileStat.st_mode & S_IXOTH) ? "x" : "-");
				printf("  %d  ",(int) fileStat.st_nlink);
				printf("  %s", user->pw_name);
				printf("  %s", group->gr_name);
				printf("  %lld",(long long)fileStat.st_size);

				strftime(date, 100, "%h %d %H:%M", localtime(&(fileStat.st_ctime)));

				printf("  %s",date );                  
				printf("  %s\n",name->d_name);
			}
		else{
				perror("Error in stat");
			}
  	  	
		printf("\n");
		}
 
  	}
}
	closedir(curDir);
	return 0;
}


