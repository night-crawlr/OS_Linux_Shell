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
long long int pd[100005];
char* Bnames[100005];
char* Fnames[100005];
char* back_state[100005];
char* fore_state[100005];
long long int c_pr;
long long int c_fpr;
char* InbuitC[6];
pid_t shell_pgid;
struct termios shell_modes;
int shell_terminal;
void handler(int sig,siginfo_t *si, void *uap)
{   
    //fprintf(stderr,"bro signal is passed\n");
    int status;
    int index;
    int flag=0;
    pid_t pid=si->si_pid;
    //waitpid(pid,&status,0);
    //fprintf(stderr,"%d\n",pid);
    for(long long int p=0;p<c_pr;p++)
    {
        if(pd[p]==0)
        continue;
        if(pid==pd[p])
        {
            pd[p]=0;
            index=p;
            flag=1;
        }
    }
    if(flag==0)
    {
        return;
    }
    if(WIFEXITED(status))
    {
        fprintf(stderr,"\n%s with pid %d exited normally with status %d\n",Bnames[index],pid,WEXITSTATUS(status));
    }
    else
    {
        fprintf(stderr,"\n%s with pid %d doesnot exited normally\n",Bnames[index],pid);
    }
}
int main()
{
    shell_terminal=STDIN_FILENO;
    while (tcgetpgrp (shell_terminal) != (shell_pgid = getpgrp ()))
        kill (- shell_pgid, SIGTTIN);
    // Ingnore some signals
    signal (SIGINT, SIG_IGN);
    signal (SIGQUIT, SIG_IGN);
    signal (SIGTSTP, SIG_IGN);
    signal (SIGTTIN, SIG_IGN);
    signal (SIGTTOU, SIG_IGN);
    //shell in its own process grp
    shell_pgid = getpid ();
    if (setpgid (shell_pgid, shell_pgid) < 0)
    {
        perror ("Couldn't put the shell in its own process group");
        exit (1);
    }
    // grabing control of terminal from shell and saving ints attrinbutes
    tcsetpgrp (shell_terminal, shell_pgid);
    tcgetattr (shell_terminal, &shell_modes);
    InbuitC[0]="cd";
    InbuitC[1]="pwd";
    InbuitC[2]="echo";
    InbuitC[3]="ls";
    InbuitC[4]="pinfo";
    InbuitC[5]="history";   
    using_history ();
    read_history(NULL);
    char home[100000]="";
    getcwd(home,sizeof(home));
    int iteration=0;
    while(1)
    {
        //fprintf(stderr,"ITERATION %d\n\n",iteration);
        iteration++;
        struct sigaction sa;
        memset(&sa, 0, sizeof(sa));
        sa.sa_sigaction = handler;
        sa.sa_flags=SA_SIGINFO | SA_RESTART | SA_NOCLDSTOP;
        sigaction(SIGCHLD,&sa,NULL);
        //signal(SIGCHLD,handler);
        //fprintf(stderr,"bro no print bro\n");
        display(home);
        char *statement[100];
        char* input;
        size_t size=10000;
        if(getline(&input,&size,stdin)==-1)
        {
            if(feof(stdin))
            exit(EXIT_SUCCESS);
            else
            {
                perror("Sys error:");
                exit(EXIT_FAILURE);
            }
            
        }        
        
        add_history(input);
        write_history(NULL);
        if(strcmp(input,"\n")==0)
        {
            continue;
        }
        char* del="';','\n'";
        statement[1]=strtok(input,del);
    
        long long int i=2;
        while(1)
        {
            statement[i]=strtok(NULL,del);
            if(statement[i]==NULL)
            {
                i--;
                break;
            }
            i++;
        }

        char* lastdirectory;
        lastdirectory=home;
        for(long long int c=1;c<=i;c++)
        {
            char*** piped;
            piped = (char***)malloc( 50 * sizeof(char ** ));
            for(long long int index=0;index<50;index++)
            {
                piped[index]=(char**) malloc(50*sizeof(char(*)));
            }
            for(int index1=0;index1<50;index1++)
            {
                for(int index2=0;index2<50;index2++)
                {
                    piped[index1][index2]=NULL;
                }
            }
            int NoOfPipe=0;
            int NoofArgs[50];
            int** IOFile;
            IOFile = (int ** )malloc(50 * sizeof(int*));
            for(long long int index=0;index<50;index++)
            {
                IOFile[index]=(int *)malloc(2*sizeof(int));
            }
            NoOfPipe=Compute(lastdirectory,shell_modes,statement[c],piped,NoofArgs,IOFile,Bnames,Fnames,back_state,fore_state,&c_fpr,&c_pr,InbuitC,home,pd);
            if(NoOfPipe==100)
            {
                return 0;
            }
           // ExecutePipe(NoOfPipe,piped,NoofArgs,InbuitC);
            
        }
  
    }
    return 0;
}