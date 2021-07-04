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
int CheckEcho(char* cmd,long long int args,char** argv)
{
    if(strcmp(cmd,"echo")==0)
    {
        for(long long int i=1;i<=args;i++)
        {
            printf("%s",argv[i]);
        }
        printf("\n");
        return 1;
    }
    return 0;
}