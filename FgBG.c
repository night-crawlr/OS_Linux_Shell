#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<sys/signal.h>
#include<fcntl.h>
#include<sys/types.h>
#include<readline/history.h>
#include<time.h>
#include<limits.h>
#include "functions.h"
#include <termios.h>
int fg(char** argv,long long int * pd,long long int * Bnum,char** Bnames,char** Bstatus,struct termios shell_modes)
{
    if(strcmp(argv[0],"fg")!=0)
    {
        return 0;
    }
    if(argv[1]==NULL)
    {
        fprintf(stderr,"Too few arguments for fg\n");
        return 1;
    }
    int jobnumber;
   // sprintf(jobnumber,"%lld",argv[1]);
    jobnumber=atoi(argv[1]);
    printf("\n%d\n",jobnumber);
    char* name;
    pid_t pid;
    long long int jobcount=0;
    for(long long int i=0;i<*Bnum;i++)
    {
        if(pd[i]==0)
        {
            continue;
        }
        jobcount++;
        if(jobcount==jobnumber)
        {
            pid=pd[i];
        }
    }
    for (long long int i=0;i<*Bnum;i++)
    {
        /* code */
        if(pd[i]==pid)
        {
            name=Bnames[i];
            Bstatus[i]="Running";
        }
    }
    
    activate_foreground(pid,1,getpid(),shell_modes,Bnames,Bnum,Bstatus,name,pd);
}
int bg(char** argv,long long int * pd,long long int * Bnum,char** Bnames,char** Bstatus,struct termios shell_modes)
{
    if(strcmp(argv[0],"bg")!=0)
    {
        return 0;
    }
    if(argv[1]==NULL)
    {
        fprintf(stderr,"Too few arguments for fg\n");
        return 1;
    }
    int jobnumber;
    //sprintf(jobnumber,"%lld",argv[1]);
    jobnumber=atoi(argv[1]);
    printf("\n%d\n",jobnumber);
    char* name;
    pid_t pid;
    long long int jobcount=0;
    for(long long int i=0;i<*Bnum;i++)
    {
        if(pd[i]==0)
        {
            continue;
        }
        jobcount++;
        if(jobcount==jobnumber)
        {
            pid=pd[i];
        }
    }
    for (long long int i=0;i<*Bnum;i++)
    {
        /* code */
        if(pd[i]==pid)
        {
            name=Bnames[i];
            Bstatus[i]="Running";
        }
    }
    activate_background(pid,1,Bnames,Bnum,Bstatus,name,pd);
}