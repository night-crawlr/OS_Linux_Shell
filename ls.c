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
void ls_a(int type,char* file,char* home)
{

    char per[15]="";
    long long int m;
    char U[100]="";
    char G[100]="";
    long long int siz;
    char dt[100]="";
    char f[1000]="";
   
    DIR * folder;
    struct dirent * entry;
    struct stat sb;
    struct group *grp;
    struct passwd *pwd;
    if(file==NULL || (strcmp(file,"~") == 0))
    {
        if(file==NULL)
            folder=opendir(".");
        else
        {
            folder=opendir(home);
        }    
    }
    else
    {
        if(stat(file,&sb)==-1)
        {
            perror(file);
            return;
        }
        if(S_ISDIR(sb.st_mode))
        {
            folder=opendir(file);
            printf("%s:\n",file);
            if(folder == NULL)
            {
                perror("No such directory");
                return;
            }
        }
        else
        {
           // printf("boom boom\n");
            stat(file,&sb);
            m=sb.st_nlink;
            per[0]='-';
            char buf[100];
            sprintf(buf,"%o",sb.st_mode);
           // printf("%s\n",buf);
            fun(buf+strlen(buf)-3,per);
            pwd=getpwuid(sb.st_uid);
            sprintf(U,"%s",pwd->pw_name);
            grp=getgrgid(sb.st_gid);
            sprintf(G,"%s",grp->gr_name);
            siz=sb.st_size;

            time_t t = sb.st_mtime;
            struct tm *lt;
            lt=localtime(&t);
            strftime(dt, sizeof(dt), "%b %d %H:%M", lt);
        if(type==3)
        {
            printf("%s\n",file);
            return;
        }
        
        if(type==1)
        {
            if(file[0]!='.')
            {
                printf("%s\n",file);
                return;
            }
        }
        if(type==4)
        {
            printf("%s %lld %s %s %lld %s %s\n",per,m,U,G,siz,dt,file);
            return;
        }
        if(file[0]!='.')
        {
            printf("%s %lld %s %s %lld %s %s\n",per,m,U,G,siz,dt,file);
            return;
        }
        return;
        }
    }
    while((entry=readdir(folder)))
    {
        //printf("%s(%d)\n",entry->d_name,type);
        //printf("2");
        char* name;
        name =entry->d_name;
        stat(entry->d_name,&sb);
        if(S_ISDIR(sb.st_mode))
        {
            per[0]='d';
        }
        else
        {
            per[0]='-';
        }
        m=sb.st_nlink;
        char buf[100];
        sprintf(buf,"%o",sb.st_mode);
        fun(buf+strlen(buf)-3,per);
        pwd=getpwuid(sb.st_uid);
        sprintf(U,"%s",pwd->pw_name);
        grp=getgrgid(sb.st_gid);
        sprintf(G,"%s",grp->gr_name);
        siz=sb.st_size;
        
        time_t t = sb.st_mtime;
        struct tm *lt;
        lt=localtime(&t);
        strftime(dt, sizeof(dt), "%b %d %H:%M", lt);
        
        if(type==3)
        {
            printf("%s\n",name);
            continue;
        }
        
        if(type==1)
        {
            if(name[0]!='.')
            {
                printf("%s\n",name);
                continue;
            }
            continue;
        }
        if(type==4)
        {
            printf("%s %lld %s %s %lld %s %s\n",per,m,U,G,siz,dt,name);
            continue;
        }
        if(name[0]!='.')
        {
            printf("%s %lld %s %s %lld %s %s\n",per,m,U,G,siz,dt,name);
        }
        continue;
    }
}
int checkls(char *cmd,char**argv,long long int args,char* home)
{
    if(strcmp(cmd,"ls")!=0)
    {
        return 0;
    }
    int type=1,flag1=0,flag2=0,count=0;
    int flag[4]={'0','0','0','0'};
    for(long long int i=1;i<=args;i++)
    {
        if(strcmp(argv[i],"-l")==0)
        {
            flag1=1;
            flag[count]=i;
            count++;
        }
        if(strcmp(argv[i],"-a")==0)
        {
            flag2=1;
            flag[count]=i;
            count++;
        }
        if( (strcmp(argv[i],"-la")==0) || (strcmp(argv[i],"-al")==0) )
        {
            flag1=1;
            flag2=1;
            flag[count]=i;
            count++;
        }
    }
    if(flag2 == 1)
    {
        type=3;
    }
    if(flag1 == 1)
    {
        type=2;
    }
    if(flag1 + flag2 == 2)
    {
        type=4;
    }
    if(args == count)
    {
        ls_a(type,NULL,home);
    }
    else
    {
        for(long long int i=1;i<=args;i++)
        {
            if(i==flag[0] || i==flag[1])
            {
                continue;
            }
            ls_a(type,argv[i],home);
        }
    }
    return 1;
}