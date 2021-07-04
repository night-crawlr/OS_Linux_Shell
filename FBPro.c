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
#include<grp.h>
#include<pwd.h>
#include<readline/history.h>
#include<time.h>
#include<limits.h>
#include "functions.h"
#include <termios.h>
void activate_foreground(pid_t pgid,int cont,pid_t shell_pid,struct termios shell_modes,char** Bnames,long long int *Bnum,char** Bstate,char* name,long long int * Bpids)
{
    struct termios tmodes;
    // giving terminal acces to foreground process
    tcsetpgrp(STDIN_FILENO,pgid);
    int stat;
//we send continue only if needed
    if(cont)
    {
        tcsetattr (STDIN_FILENO, TCSADRAIN, &tmodes);
      if (kill (- pgid, SIGCONT) < 0)
        perror ("kill (SIGCONT)");
    }
    waitpid(pgid,&stat,WUNTRACED);
    //keeping shell in background
    tcsetpgrp (STDIN_FILENO, shell_pid);

    //restore shell terminal modes
    tcgetattr (STDIN_FILENO, &tmodes);
  tcsetattr (STDIN_FILENO, TCSADRAIN, &shell_modes);
  //printf("YoYoYoYo\n");
    if (WIFEXITED(stat))
    {
       fprintf(stderr,"\nForeground process exited normally with exit status %d\n",WEXITSTATUS(stat));
    }
    else
    {
        //fprintf(stderr,"fwefwefwef\n");
        
        if(WTERMSIG(stat)==2)
        {
            /* code */
            fprintf(stderr,"Process got interupted by ctrl + c and exited\n");
            return;
        }
            fprintf(stderr,"\nProcess got interupted by ctrl + Z changing process to background................\n");
            Bnames[*Bnum]=name;
            printf("%s %s\n",name,Bnames[*Bnum]);
            Bstate[*Bnum]="Stopped";
            Bpids[*Bnum]=pgid;
            *Bnum=*Bnum+1;
    }
    
}
void activate_background(pid_t pgid,int cont,char** Bnames,long long int *Bnum,char** Bstate,char* name,long long int * Bpids)
{
if (cont)
{
    if (kill (-pgid, SIGCONT) < 0)
    perror ("kill (SIGCONT)");
}
}