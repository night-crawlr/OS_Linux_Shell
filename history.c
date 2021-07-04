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
int is_history(char* cmd,long long int args,char ** argv)
{
    if(strcmp("history",cmd)==0)
    {
        int no;
        if(args==0)
        {
            no=10;
        }
        else
        {
            sscanf(argv[1],"%d",&no);
        }
        if(no > 20)
        {
            printf("Sorry only 20 cmd available\n");
            no=20;
        }
        HISTORY_STATE * state;
        state=history_get_history_state();
        if(no > state->length)
        {
            no=state->length;
        }
        for(long long int h=0;h<no;h++)
        {
            printf("%s\n",(state->entries[state->length -1 -h])->line);
        }
        return 1;
    }
    return 0;
}