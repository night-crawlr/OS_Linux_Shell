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
void display(char* home)
{
    char* name=getenv("USER");
    char hostname[100000]="";
    gethostname(hostname,sizeof(hostname));
    char pwd[100000]="";
    getcwd(pwd,sizeof(pwd));
    char cwd[100000]="";
    convert(pwd,home,cwd);
    printf("<%s@%s:%s>",name,hostname,cwd); 
}