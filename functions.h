#ifndef FUNCTIONS_H
#define FUNCTIONS_H
#include <termios.h>
void display(char* home); 
char* convert (char* loc,char* home,char* name); 
char* undo(char* loc,char* home,char* name); 
long long int TakeInput(char** argv,char * input);  
int is_history(char* cmd,long long int args,char ** argv);
int ProcessInput(char* cmd,char** argv,long long int args,char* home); 
void ls_a(int type,char* file,char* home);
void fun(char * buf,char * per);
int checkls(char *cmd,char**argv,long long int args,char* home);
int ispinfo(char ** argv,long long int args);
int isand(char ** argv,long long int args,long long int *pd,char ** cooo,long long int *c_pr);
int CheckCd(char* lastdirectory,char* cmd,long long int args,char** argv,char* home);
int CheckPWD(char * cmd);
int CheckEcho(char* cmd,long long int args,char** argv);
int Compute(char* lastdirectory,struct termios shell_modes,char* input,char*** piped,int* NoofArgs,int** IOFile,char** Bnames,char** Fnames,char** Bstatus,char** Fstatus,long long int*Fnum ,long long int* Bnum,char** InbuiltC,char* home,long long int * pd);
int Redirect(char** argv,int* IO,int args);
int Setenv(char** argv,long long int  args);
int Unsetenv(char** argv,long long int args);
void activate_foreground(pid_t pgid,int cont,pid_t shell_pid,struct termios shell_modes,char** Bnames,long long int *Bnum,char** Bstate,char* name,long long int * Bpids);
void activate_background(pid_t pgid,int cont,char** Bnames,long long int *Bnum,char** Bstate,char* name,long long int * Bpids);
int jobs(char* cmd,long long int * pd,long long int * Bnum,char** Bnames,char** Bstatus);
int fg(char** argv,long long int * pd,long long int * Bnum,char** Bnames,char** Bstatus,struct termios shell_modes);
int bg(char** argv,long long int * pd,long long int * Bnum,char** Bnames,char** Bstatus,struct termios shell_modes);
int overkill(long long int * pd,long long int * Bnum,char** argv,long long int args);
int kjob(char** argv,long long int args,long long int * pd,long long int * Bnum);
#endif