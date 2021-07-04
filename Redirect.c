#include<stdio.h>
#include<string.h>
#include<stdlib.h>
#include<unistd.h>
#include<dirent.h>
#include<sys/stat.h>
#include<sys/wait.h>
#include<fcntl.h>
#include<sys/types.h>
#include<grp.h>
#include<pwd.h>
#include<readline/history.h>
#include<time.h>
#include<limits.h>
#include "functions.h"
int Redirect(char** argv,int* IO,int args)
{
    IO[0]=0;
    IO[1]=1;
    // searching in argv from index 1 to args for ">>" | ">" | "<"
    int i=0;
    int firstIO=-5,type1IO=-5;
    char* IF;
    char* OF;
    for(i=0;i<=args;i++)
    {
        if(strcmp(argv[i],">>")==0)
        {
            firstIO=i;
            type1IO=1;
            break;
        }
        if(strcmp(argv[i],">")==0)
        {
          firstIO=i;
          type1IO=2;
          break;
        }
        if (strcmp(argv[i],"<")==0)
        {
            firstIO=i;
            type1IO=3;
            break;
        }
    }
    if(firstIO==-5)
    {
        return args;
    }

    int secondIO=-5,type2IO=-5;
    for(i=0;i<=args;i++)
    {
        if(i==firstIO)
        {
            continue;
        }
        if(strcmp(argv[i],">>")==0)
        {
            secondIO=i;
            type2IO=1;
            break;
        }
        if(strcmp(argv[i],">")==0)
        {
          secondIO=i;
          type2IO=2;
          break;
        }
        if (strcmp(argv[i],"<")==0)
        {
            secondIO=i;
            type2IO=3;
            break;
        }
    }
    char** New;
    New = (char**) malloc( (args+5) * sizeof(char*));
    for(long long int index=0;index<=(args+4);index++)
    {
        New[index]=NULL;
    }
    int N_i=0;
    for(i=0;i<=args;i++)
    {
        if(i==firstIO || i == (firstIO + 1) || i == secondIO || i== (secondIO + 1))
        {
            continue;
        }  
        New[N_i]=argv[i];
        N_i++;
    }

    if(type1IO==1)  //output append
    {
        if(argv[firstIO+1]==NULL)
        {
            fprintf(stderr,"Name of file not specified\n");
        }
        int fd = open(argv[firstIO+1],O_RDWR | O_CREAT | O_APPEND,0777);
        IO[1]=fd;
    }
    else if(type1IO == 2) //output redirect
    {
        if(argv[firstIO+1]==NULL)
        {
            fprintf(stderr,"Name of file not specified\n");
        }
        int fd = open(argv[firstIO+1],O_RDWR | O_CREAT | O_TRUNC,0777);
        IO[1]=fd;
    }
    else // input redirect
    {
        if(argv[firstIO+1]==NULL)
        {
            fprintf(stderr,"Name of file not specified\n");
        }
        int fd = open(argv[firstIO+1],O_RDONLY,0777);
        if(fd == -1)
        {
            perror(argv[firstIO+1]);
        }
        IO[0]=fd;
    }
    if(type2IO != -5)
    {
    if(type2IO==1)  //output append
    {
        if(argv[secondIO+1]==NULL)
        {
            fprintf(stderr,"Name of file not specified\n");
        }
        int fd = open(argv[secondIO+1],O_RDWR | O_CREAT | O_APPEND,0777);
        IO[1]=fd;
    }
    else if(type2IO == 2) //output redirect
    {
        if(argv[secondIO+1]==NULL)
        {
            fprintf(stderr,"Name of file not specified\n");
        }
        int fd = open(argv[secondIO+1],O_RDWR | O_CREAT | O_TRUNC,0777);
        IO[1]=fd;
    }
    else // input redirect
    {
        if(argv[secondIO+1]==NULL)
        {
            fprintf(stderr,"Name of file not specified\n");
        }
        int fd = open(argv[secondIO+1],O_RDONLY,0777);
        if(fd==-1)
        {
            perror(argv[secondIO+1]);
        }
        IO[0]=fd;
    }
    }
    for(int index=0;index<=args;index++)
    {
        argv[index]=NULL;
    }
    args=N_i-1;
    for(int index=0;index<=args;index++)
    {
        argv[index]=New[index];
    }
    /*printf("firstio  %d   secondio %d \n",firstIO,secondIO);
    for(int index=0;index<=5;index++)
    {
        fprintf(stderr,"(%s)\n",argv[index]);

    }*/
    return args;
}