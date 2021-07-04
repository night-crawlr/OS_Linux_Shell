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
int CheckPWD(char* cmd)
{
    if(strcmp(cmd,"pwd")==0)
    {
        char pwd[100000]="";
        getcwd(pwd,sizeof(pwd));
        printf("%s\n",pwd);
        return 1;        
    }
    return 0;
}