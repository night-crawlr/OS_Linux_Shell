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
void fun(char * buf,char * per)
{
    int i=1;
    for(long long int i=0;i<3;i++)
    {
        buf[i]=buf[i]-48;
    }
    while(i!=10)
    {
        int j;
        j=4-i;  
        j+=6*((i-1)/3);
        if( (buf[(i-1)/3]%2) == 1)
        {       
            if(i%3 == 1)
                per[j]='x';
            if(i%3 == 2)
                per[j]='w';
            if(i%3 == 0)
                per[j]='r';
        } 
        else
        {
            per[j]='-';
        }
        
        buf[(i-1)/3]=buf[(i-1)/3]/2;
        i++;
    }
}