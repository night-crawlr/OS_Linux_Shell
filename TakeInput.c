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
long long int TakeInput(char** argv,char* input)
{
    char* del="' ','\t','\n'";
    argv[0]=strtok(input,del);
    long long int i=1;
    while(1)
    {
        argv[i]=strtok(NULL,del);
        if(argv[i]==NULL)
        {
            i--;
            break;
        }
        i++;
    }
    
    return i;
}