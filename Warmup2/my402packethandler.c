#include<stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <string.h>
#include <sys/time.h>
#include "my402main.h"
#include "my402packethandler.h"
#include "my402functionality.h"

void *packethandler(void *threadid)
{
 long packet_num=1;
 struct timeval curtime;
 struct timeval prevP=starttime;
 My402Packet *p=NULL;
 while(checktotalpackets())
 {
 if(checktotalpackets())
 {
  if(tfile==NULL)
    {
      p=deterPacket(packet_num);
    }
  else
   { 
     p=tPacket(packet_num);
   }
  if(!checktotalpackets())
     {free(p);break;}
  gettimeofday(&curtime,NULL);
  p->parvtime=curtime;
  printPacket(p,prevP,curtime);
  total_arv_packets++;
  if(!(p->tokens>B))
  {
  pthread_mutex_lock(&m);
  My402ListAppend(Q1,p);
  pthread_mutex_unlock(&m);
  gettimeofday(&curtime,NULL);
  p->eQ1=curtime;
  pthread_mutex_lock(&m);
  printTimeDiff(curtime);
  printf("p%ld enters Q1\n",p->packet_num);
  pthread_mutex_unlock(&m);
  }
  else
  {
  free(p);
  }
  prevP=curtime;
  packet_num++;
  }
  checkPacketshift();
 }
 pthread_exit(NULL);
}


void printPacket(My402Packet * p,struct timeval prevP,struct timeval curtime)
{
 double millisec=timediff(prevP,curtime);
 total_inter_arv+=millisec;
 pthread_mutex_lock(&m);
 total_Packets--;
 printTimeDiff(curtime);
 if(p->tokens>B)
  {
    packetdrop++;
    printf("p%ld arrives, needs %d tokens, inter-arrival time = %.3fms, dropped\n",p->packet_num,p->tokens,millisec);
  }
  else
  {
   printf("p%ld arrives, needs %d tokens, inter-arrival time = %.3fms\n",p->packet_num,p->tokens,millisec);
  }
  pthread_mutex_unlock(&m);
}

My402Packet * genereatePacket(long packet_num,int tokens,double servicetime)
{
 My402Packet *p=(My402Packet *)malloc(sizeof(My402Packet));
 p->packet_num=packet_num;
 p->tokens=tokens;
 p->service_time=servicetime;
 return p;
}

My402Packet * deterPacket(long packet_num)
{
  double sec=1000000/lambda;
  double servtime=1000000/mu;
  if(sec>10000000)
   sec=10000000;
  if(servtime>10000000)
   servtime=10000000;
  My402Packet *p=genereatePacket(packet_num,P,servtime);
  usleep(sec);
  return p;
}

My402Packet * tPacket(long packet_num)
{
 char line[100];
 char *stoken=NULL;
 int i,delim=0;
 long tneeded,s_time,in_arv_time;
 My402Packet *p=NULL;
 if(fgets(line, sizeof(line), tfile)!=NULL)
 {
 int len=strlen(line);
  for(i=0;i<len;i++)
   {
    
    if(line[i]==' ')
     {
      if(delim==0)
        {
         stoken=strtok(line," ");
	      delim++;
	    }
       else
        {
         stoken=strtok(NULL," ");
         delim++;
        }	
     } 
    else if(line[i]=='\t')
     {
      if(delim==0)
        {
         stoken=strtok(line,"\t");
	      delim++;
	    }
       else
        {
         stoken=strtok(NULL,"\t");
         delim++; 
        }   
     }
    else if(line[i]=='\n'||line[i]=='\0')
     {
         stoken=strtok(NULL,"\t");
         delim++;
     }
     if(stoken!=NULL)
      {
       if(delim==1)
         in_arv_time=atoi(stoken);
       else if(delim==2)
         tneeded=atoi(stoken);
       else if(delim==3)
         s_time=atoi(stoken)*1000;
       stoken=NULL;
      }
   }
   p=genereatePacket(packet_num,tneeded,s_time);
   if(in_arv_time*1000>10000000)
    in_arv_time=10000;
   usleep(in_arv_time*1000);
  }
  return p;
}