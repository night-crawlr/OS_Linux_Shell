#include<stdio.h>
#include<string.h> 
#include<signal.h>
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h>
#include<sys/stat.h>
#include<sys/signal.h>
#include<fcntl.h>
#include<readline/history.h>
#include "functions.h" 
#include <termios.h>
int jobs(char* cmd,long long int * pd,long long int * Bnum,char** Bnames,char** Bstatus)
{
    if(strcmp(cmd,"jobs")!=0)
    {
        return 0;
    }
    long long int jobcount=0;
for(long long int i=0;i<*Bnum;i++)
{
    if(pd[i]==0)
    {
        continue;
    }
    jobcount++;
    printf("[%lld] %s %s [%lld]\n",jobcount,Bstatus[i],Bnames[i],pd[i]);   
}
if(jobcount==0)
{
    fprintf(stderr,"No current Background jobs\n");
}
return 1;
}