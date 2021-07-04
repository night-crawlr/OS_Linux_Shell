#include<stdio.h>
#include<string.h> 
#include<signal.h>
#include<stdlib.h> 
#include<unistd.h> 
#include<sys/types.h> 
#include<sys/wait.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<readline/history.h>
#include "functions.h" 
int Setenv(char** argv,long long int args)
{
    if(strcmp(argv[0],"setenv")!=0)
    {
        return 0;
    }
    if(args!=2)
    {
        fprintf(stderr,"Error in executing setenv -> Fault in Number of arguments\n");
        return 1;
    }
    if((setenv(argv[1],argv[2],1))!=0)
    {
    perror("Error"); 
    }
    return 1;
}
int Unsetenv(char** argv,long long int args)
{
    if (strcmp(argv[0],"unsetenv")!=0)
    {
        return 0;
    }
    if (args!=1)
    {
        /* code */
        fprintf(stderr,"Error in exectuind unsetenv -> Fault in Number of arguments\n");
        return 1;
    }
    if((unsetenv(argv[1]))!=0)
    {
        perror("Error");
    }
    return 1;
}