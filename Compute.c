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
#include<readline/history.h>
#include<time.h>
#include<limits.h>
#include "functions.h"
#include <termios.h>
int Compute(char* lastdirectory,struct termios shell_modes,char* input,char*** piped,int* NoofArgs,int** IOFile,char** Bnames,char** Fnames,char** Bstatus,char** Fstatus,long long int*Fnum ,long long int* Bnum,char** InbuiltC,char* home,long long int * pd)
{
    //These two lines are used for restoring IO for this process wjen inbuilt are executed under redirection
    int Restore_I=dup(STDIN_FILENO);
    int Restore_O=dup(STDOUT_FILENO);
    
    int stat;
    char* del="|";
    char* instruct[100];
    instruct[0] = strtok(input,del);
    // i+1 contains no of arguments seperated with pipes
    int i=1;
    while (1)
    {
        instruct[i]=strtok(NULL,del);
        if(instruct[i]==NULL)
        {
            i--;
            break;
        }
        i++;
    }
    if(instruct[0]==NULL)
    {
        return 0;   
    }
    /*
    for(int j=0;j<(i+1);j++)
    {
        printf("(%s)\n",instruct[j]);
    }
    printf("There are %d commands\n",i+1);
    return i+1;
    */
    int background=0;
    for(long long int j=0;j<(i+1);j++)
    {
        NoofArgs[j]=TakeInput(piped[j],instruct[j]);
    }
    if(strcmp(piped[i][NoofArgs[i]],"&")==0)
    {
      //  fprintf(stderr,"this is back\n");
        background=1;
        piped[i][NoofArgs[i]]=NULL;
        NoofArgs[i]--;
    }
    //piped[j] is array of command and its arguments and NofArgs[j] is no of arguments of that command piped[j][0]
    int fd[2]; //creating pipe fds
    int PrevOUt=0;
    for(long long int j=0;j<(i+1);j++) // each j refers to each command in pipe instruction
    {
        if (piped[j][0]==NULL)
        {
           return 0;
        }
       
        if(pipe(fd)==-1)
        {
            perror("sys err");
            return 0;
        }
        // checking if cmd is inbuiti or syscommand
        if((strcmp("overkill",piped[j][0])==0)||(strcmp("kjob",piped[j][0])==0)||(strcmp(piped[j][0],"fg")==0)||(strcmp(piped[j][0],"bg")==0)||(strcmp(piped[j][0],"jobs")==0)||(strcmp(piped[j][0],"quit")==0) || (strcmp(piped[j][0],"cd")==0) || (strcmp(piped[j][0],"echo")==0) || (strcmp(piped[j][0],"ls")==0) || (strcmp(piped[j][0],"pwd")==0)|| (strcmp(piped[j][0],"pinfo")==0) || (strcmp(piped[j][0],"history")==0) || (strcmp(piped[j][0],"setenv")==0) || (strcmp(piped[j][0],"unsetenv"))==0 )
        {
            if (strcmp(piped[j][0],"quit")==0)
            {
                return 100;
            }
            
            //kontha sepati lo ikkasdiki vasta agu
            NoofArgs[j]=Redirect(piped[j],IOFile[j],NoofArgs[j]); //redirect gives us input and output file for command and net number of arguments after removing ">" and other such thing 
            if(IOFile[j][0]==-1)
            {
                return 0 ;
            }
            // redirecting the input output of child process
            if(j!=0) // changing input of cmd to previous output if it is not first command
            {
                dup2(PrevOUt,STDIN_FILENO); // changing the input of cmd to previous out pipe
            }
            else
            {
                if(IOFile[j][0]==-1)
                {
                    IOFile[j][0]=0;
                }
                dup2(IOFile[j][0],STDIN_FILENO);// if it is first command chaging input according to its wish
            }
            
            if(j!=i) // change output of process to pipe if its not last command in pipe
            {
            dup2(fd[1],STDOUT_FILENO); // changing the output of command to next pipe
            }
            else
            {
                dup2(IOFile[j][1],STDOUT_FILENO);
            }
            if(IOFile[j][1]!=1) // specifically output is mentioned
            {
                dup2(IOFile[j][1],STDOUT_FILENO); // redirecting the output
                /*tf(stderr,"Cannot execute next command ie %lld thas output got redirected",j+1);
                    return 0;
                    Donot=1;
                }*/
            }

            //close(fd[0]);
            close(fd[1]);
            PrevOUt=fd[0];
            if((overkill(pd,Bnum,piped[j],NoofArgs[j])==1)|| (kjob(piped[j],NoofArgs[j],pd,Bnum)==1)||(fg(piped[j],pd,Bnum,Bnames,Bstatus,shell_modes)==1)||(bg(piped[j],pd,Bnum,Bnames,Bstatus,shell_modes)==1)||(jobs(piped[j][0],pd,Bnum,Bnames,Bstatus)==1)||(CheckCd(lastdirectory,piped[j][0],NoofArgs[j],piped[j],home) ==1) || (CheckEcho(piped[j][0],NoofArgs[j],piped[j]) == 1) || (CheckPWD(piped[j][0]) ==1 ) || (checkls(piped[j][0],piped[j],NoofArgs[j],home) == 1) || (is_history(piped[j][0],NoofArgs[j],piped[j]) == 1) || (ispinfo(piped[j],NoofArgs[j]) == 1)|| (Setenv(piped[j],NoofArgs[j]) == 1) || (Unsetenv(piped[j],NoofArgs[j])==1))
            {
                // actually we exucted inbuilt command in main process but it changed the IO redirection so after executing I am restoring the original IO's
                //to restoring SDIN STDOUT first we store it seperatly in other fd's
                //we will definetly enter this loop
                dup2(Restore_I,STDIN_FILENO);
                dup2(Restore_O,STDOUT_FILENO);
            }
            continue;
        }
            
        NoofArgs[j]=Redirect(piped[j],IOFile[j],NoofArgs[j]); //redirect gives us input and output file for command and net number of arguments after removing ">" and other such thing        
        if(IOFile[j][0]==-1)
        {
            return 0 ;
        }
        
        pid_t pid=fork();
        pid_t pgid=pid;
    
        if(pid==-1)
        {
           perror("sys err");
           return 0;
        }
        if(background)
        {
            Bnames[*Bnum]=instruct[j];
            pd[*Bnum]=pid;
            Bstatus[*Bnum]="Running";
            *Bnum=*Bnum+1;
        }
        setpgid(pid,pgid);
        //checking if piped[j][0] is background or not
       
       /* int background=0;
        if(strcmp(piped[j][NoofArgs[j]],"&")==0) // checking last elemnt in piped[j]
        {
            background=1;
            piped[j][NoofArgs[j]]=NULL;
            Bnames[*num]=piped[j][0];
            pd[*num]=pid;
            *num=*num + 1;
            NoofArgs[j]=NoofArgs[j]-1;
            //fprintf(stderr,"yes iam noting with %d\n",pid);
        }*/
       
       /* for(long long int index=0;index<=5;index++)
        {
            fprintf(stderr,"1(%s)\n",piped[j][index]);
        }*//*
        if(j!=i && IOFile[j][1]!=1)
        {
            fprintf(stderr,"Cannot execute next command ie %lldth as output got redirected",j+1);
            Donot=1;
        }*/
        if(pid==0)
        {
            //fprintf(stderr,"(%s)",piped[j][0]);
            //child process
            // redirecting the input output of child process
            pid=getpid();
            if(pgid==0)
            {
                pgid=pid;
            }
            setpgid(pid,pgid);
            if(!background)
            {
                tcsetpgrp (STDIN_FILENO, pgid);
            }
            signal (SIGINT, SIG_DFL);
            signal (SIGQUIT, SIG_DFL);
            signal (SIGTSTP, SIG_DFL);
            signal (SIGTTIN, SIG_DFL);
            signal (SIGTTOU, SIG_DFL);
            signal (SIGCHLD, SIG_DFL);
            if(j!=0) // changing input of cmd to previous output if it is not first command
            {
                if(IOFile[j][0]==0)
                dup2(PrevOUt,STDIN_FILENO); // changing the input of cmd to previous out pipe
                if (IOFile[j][0]!=0)
                {
                dup2(IOFile[j][0],STDIN_FILENO);
                }
                
            }
            else
            {
                dup2(IOFile[j][0],STDIN_FILENO);// if it is first command chaging input according to its wish
            }
            
            if(j!=i) // change output of process to pipe if its not last command in pipe
            {
            dup2(fd[1],STDOUT_FILENO); // changing the output of command to next pipe
            }
            else
            {
                dup2(IOFile[j][1],STDOUT_FILENO);
            }
            if(IOFile[j][1]!=1) // specifically output is mentioned
            {
                dup2(IOFile[j][1],STDOUT_FILENO); // redirecting the output
            }
            close(fd[0]);
            close(fd[1]);
            
            execvp(piped[j][0],piped[j]);
            perror("execvp");
            exit(1);
        }
        // this is parent process ie shell
        if( i+1 == 1)
        {
            if(!background)
            {
                activate_foreground(pgid,0,getpid(),shell_modes,Bnames,Bnum,Bstatus,piped[j][0],pd);
            }
            else
            {
                activate_background(pgid,0,Bnames,Bnum,Bstatus,piped[j][0],pd);
            } 
            return 0;   
        }
        if(!background)
        {
            activate_foreground(pgid,0,getpid(),shell_modes,Bnames,Bnum,Bstatus,piped[j][0],pd);
        }
        else
        {
            activate_background(pgid,0,Bnames,Bnum,Bstatus,piped[j][0],pd);
        }
        close(fd[1]);
        PrevOUt=fd[0];

    }
}