#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <math.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include "my402main.h"
#include "my402functionality.h"

double checkNum(char *value)
{
 int i,len=strlen(value);
 double num;
 char *tok;
 for(i=0;i<len;i++)
  {
   if(!(isdigit(value[i])||value[i]=='.'))
     return -1;
  } 
 tok=strtok(value,".");
 num=atoi(tok);
 tok=strtok(NULL,".");
 if(tok!=NULL)
  {
  len=strlen(tok);
   num+=atoi(tok)*pow(10,-len);
  }
  return num;
}

void checkCommandLine(int argc,char *argv[])
{
 int i;
 char n[12];
 for( i=1;i<argc;i++)
  {
   if(strcmp(argv[i],"-n")==0)
    {
     total_Packets=(int)checkNum(argv[i+1]);
     if(total_Packets==-1)
      {
       fprintf(stderr, "Input value of n is not a number.\nAbort program.\n");
       exit(EXIT_FAILURE);
      }
     i++;
    }
   else if (strcmp(argv[i],"-lambda")==0)
    {
     lambda=(double)checkNum(argv[i+1]);
     if(lambda==-1)
      {
       fprintf(stderr, "Input value of lambda is not a number.\nAbort program.\n");
       exit(EXIT_FAILURE);
      }
     i++;
    }
   else if (strcmp(argv[i],"-mu")==0)
   {
     mu=(double)checkNum(argv[i+1]);
     if(mu==-1)
      {
       fprintf(stderr, "Input value of mu is not a number.\nAbort program.\n");
       exit(EXIT_FAILURE);
      }
     i++;
    }
   else if (strcmp(argv[i],"-r")==0)
   {
     r=(double)checkNum(argv[i+1]);
     if(r==-1)
      {
       fprintf(stderr, "Input value of r is not a number.\nAbort program.\n");
       exit(EXIT_FAILURE);
      }
     i++;
    }
   else if (strcmp(argv[i],"-B")==0)
   {
     B=(int)checkNum(argv[i+1]);
     if(B==-1)
      {
       fprintf(stderr, "Input value of B is not a number.\nAbort program.\n");
       exit(EXIT_FAILURE);
      }
     i++;
    }
   else if (strcmp(argv[i],"-P")==0)
   {
     P=(int)checkNum(argv[i+1]);
     if(P==-1)
      {
       fprintf(stderr, "Input value of P is not a number.\nAbort program.\n");
       exit(EXIT_FAILURE);
      }
     i++;
    }
   else if (strcmp(argv[i],"-t")==0)
   {
     tracefile=(char *)malloc(strlen(argv[i+1])*sizeof(char));
     strcpy(tracefile,argv[i+1]);
     tfile=getFilePointer(tracefile);
      if(fgets(n, sizeof(n), tfile)!=NULL)
        {
         n[strlen(n)-1]='\0';
         total_Packets=(int)checkNum(n);
         if(total_Packets>2147483647)
           {
   	    fprintf(stderr, "Input value of n in file is  greater than 2147483647.\nAbort program.\n");
   	    fclose(tfile);
            exit(EXIT_FAILURE);
           }
         else if(total_Packets==-1)
          {
           fprintf(stderr, "Input value of n is not a number.\nAbort program.\n");
           fclose(tfile);
           exit(EXIT_FAILURE);
          }
        }
     i++;
    }
   else
   {
    fprintf(stderr, "Malformed Command.\nUnknown arguments are passed.\n");
    exit(EXIT_FAILURE);
   }
  }
}

FILE* getFilePointer(char* tracefile)
{
    FILE *tfile=NULL;
     struct stat fs;
    if( stat(tracefile,&fs) == 0 )
    {
     if(S_ISDIR(fs.st_mode))
      {
       fprintf(stderr,"Input file at %s is a directory.\nPlease check the file path.\n",tracefile);
       exit(EXIT_FAILURE);
      }
     else if(S_ISREG(fs.st_mode))
      {
       tfile=fopen(tracefile,"r");
       if(tfile==NULL)
       {
        fprintf(stderr,"Input file %s cannot be opened -%s\n",tracefile,strerror(errno));
        exit(EXIT_FAILURE);
       }
      }
     else
      {
       fprintf(stderr,"Input file at %s is improper.\nPlease check the file path.\n",tracefile);
       exit(EXIT_FAILURE);
      }
    }
    else
     {
      fprintf(stderr,"Input file at %s doesnot exist or cannot be accessed.\nPlease check the file path.\n",tracefile);
      exit(EXIT_FAILURE);
     }
  return tfile;
}

void printTimeDiff(struct timeval tv1)
{

 time_t diffsec=tv1.tv_sec-starttime.tv_sec;
 double microsec=(diffsec*1000000)+tv1.tv_usec-starttime.tv_usec;
 double millisec=microsec/1000;
 if(microsec>=100000000000)
 printf("????????.???ms: ");
 else
  {
   printf("%012.3fms: ",millisec);
  }
}

void checkPacketshift()
{
 int broadcast=0;
 struct timeval curtime;
  if(!checkQempty(Q1))
    {
     pthread_mutex_lock(&m);
     My402ListElem *elem=My402ListFirst(Q1);
     if(elem!=NULL)
     {
     My402Packet * p=(My402Packet *)(elem->obj);
     if(p->tokens<=curB)
       {
        My402ListUnlink(Q1, My402ListFirst(Q1));
        pthread_mutex_unlock(&m);
        gettimeofday(&curtime,NULL);
        double timeQ1=timediff(p->eQ1,curtime);
	p->timeinQ1=timeQ1;
        pthread_mutex_lock(&m);
        curB-=p->tokens;
        printTimeDiff(curtime);
        printf("p%ld leaves Q1, time in Q1 = %.3fms, token bucket now has %d token\n" ,p->packet_num,timeQ1,curB);		
        if(My402ListEmpty(Q2))
           broadcast=1;
        My402ListAppend(Q2, p);
        gettimeofday(&curtime,NULL);
        printTimeDiff(curtime);
        p->eQ2=curtime;
        printf("p%ld enters Q2\n" ,p->packet_num);
        pthread_mutex_unlock(&m);
        if(broadcast==1)
         pthread_cond_broadcast(&cond_t);
       }
       else
       {
       pthread_mutex_unlock(&m);
       }
     }
    }
    else if(!checktotalpackets()&&checkQempty(Q1))
    {
     pthread_cond_broadcast(&cond_t);
    }
}

double timediff(struct timeval t1,struct timeval t2)
{
 time_t diffsec=t2.tv_sec-t1.tv_sec;
 double microsec=(diffsec*1000000)+t2.tv_usec-t1.tv_usec;
 double millisec=microsec/1000;
 return millisec;
}

int checkQempty(My402List *Q)
{
  pthread_mutex_lock(&m);
  int check=My402ListEmpty(Q);
  pthread_mutex_unlock(&m);
  return check;
}

int checktotalpackets()
{
  pthread_mutex_lock(&m);
  int check=total_Packets>0;
 // printf("Total Packets:%d",totoal_Packets);
  pthread_mutex_unlock(&m);
  return check;
}

double calstddev(double Ex2,double Ex,int n)
{
  if(n==0)
    return 0; 
  double Exn=(Ex/n);
  double var=(Ex2/n)-Exn*Exn;
  double stddev=sqrt(var);
  return stddev;

}