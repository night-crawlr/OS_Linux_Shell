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
int ispinfo(char ** argv,long long int args)
{
    if(strcmp(argv[0],"pinfo")!=0)
    {
        return 0;
    }
    long long int pid;
    if(args>1)
    {
        printf("Too many arguments\n");
        return 1;
    }
    if(args==0)
    {
        pid=getpid();
    }
    else
    {
        sscanf(argv[1],"%lld",&pid);
    }
    int fd1,fd2,fd3;
    char file1[10000]="";char file2[10000]="";char file3[10000]="";
    char name1[10000]="";char exe[10000]="";char name3[10000]="";
    char * name;
    char* state;
    char *pids;
    int memory;
    sprintf(file1,"/proc/%lld/stat",pid);
    sprintf(file3,"/proc/%lld/exe",pid);    
    fd1=open(file1,O_RDONLY);
    FILE * ptr1=fopen(file1,"r");
    if(ptr1 == NULL)
    {
        printf("No such process with pid\n");
        return 1;
    }
    FILE * ptr2=fopen(file2,"r");
    fscanf(ptr1,"%[^\n]s",name1);
    char del[50]=" ";
    pids=strtok(name1,del);
    name=strtok(NULL,del);
    state=strtok(NULL,del);
    char * dum;
    for(long long int ds=0;ds<20;ds++)
    {
        dum=strtok(NULL,del);
    }
    readlink(file3,exe,10000);
    printf("pid -- %s\n",pids);
    printf("Process Status -- %s\n",state);
    printf("memory -- %s\n",dum);
    printf("Executable path -- %s\n",exe);
    return 1;
}