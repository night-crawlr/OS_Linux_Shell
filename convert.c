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
char* convert (char* loc,char* home,char* name)
{   
    if(strlen(loc) < strlen(home))
    {
        long long int s=strlen(loc);
        for(long long int z=0;z<s;z++)
        {
            name[z]=loc[z];
        }
        return name;
    }
    int i;
    int j=1;
    int size_home=strlen(home);
    int size_loc=strlen(loc);
    name[0]='~';
    for(i=0;i<size_home;i++)    
    for(i=size_home;i<size_loc;i++)
    {
        name[j]=loc[i];
        j++;
    }
    return name;
}