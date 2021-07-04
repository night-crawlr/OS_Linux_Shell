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
int kjob(char** argv,long long int args,long long int * pd,long long int * Bnum)
{
    if(strcmp("kjob",argv[0])!=0)
    {
        return 0;
    }
    if(args != 2)
    {
  fprintf(stderr,"Invalid no of argumnts\n");
}    
int jobnumber;
   // sprintf(jobnumber,"%lld",argv[1]);
    jobnumber=atoi(argv[1]);
    int sig=atoi(argv[2]);
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
    if(kill(pid,sig) == -1)
    {
        perror("Kill error");
    }
    return 1;
}
int overkill(long long int * pd,long long int * Bnum,char** argv,long long int args)
{
    if (strcmp("overkill",argv[0])!=0)
    {
        return 0;
    }
    for(long long int i=0;i<*Bnum;i++)
    {
        if(pd[i]==0)
        {
            continue;
        }
        kill(pd[i],9);
    }
    return 1;
}