#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<sys/types.h>
#include<grp.h>
#include<pwd.h>
#include<readline/history.h>
#include<time.h>
#include<limits.h>
#include "functions.h"
int CheckCd(char* lastdirectory,char* cmd,long long int args,char** argv,char* home)
{
    if(strcmp(cmd,"cd")==0)
    {

        if(args==0)
        {
            char yoyo[10000]="";
            getcwd(yoyo,sizeof(yoyo));
            lastdirectory=yoyo;
            chdir(home);
            return 1;
        }
        if(args>1)
        {
            printf("cd: Too many arguments\n");
            return 1;
        }
        if(strcmp(argv[1],"~")==0)
        {
                        char yoyo[10000]="";
            getcwd(yoyo,sizeof(yoyo));
            lastdirectory=yoyo;
            chdir(home);
            //lastdirectory=home;
            return 1;
        }
        if(strcmp(argv[1],"-")==0)
        {
             char yoyo[10000]="";
            getcwd(yoyo,sizeof(yoyo));
            chdir(home);
            chdir(lastdirectory);
            printf("%s\n",lastdirectory);
            lastdirectory=yoyo;
            return 1;
        }
        if(chdir(argv[1])!=0)
        {
            perror("cd:");
            return 1;
        }
        else
        {
 char yoyo[10000]="";
            getcwd(yoyo,sizeof(yoyo));
            lastdirectory=yoyo;
        }
        
        return 1;
    }
    return 0;
}