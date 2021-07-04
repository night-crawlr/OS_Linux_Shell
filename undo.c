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
char* undo(char* loc,char* home,char* name)
{
    int i;
    int j;
    int size_home=strlen(home);
    int size_loc=strlen(loc);
    for(i=0;i<size_home;i++)
    {
        name[i]=home[i];
    }
    for(j=0;j<(size_loc-1);j++)
    {
        name[i+j]=loc[j+1];
    }
    return name;
}