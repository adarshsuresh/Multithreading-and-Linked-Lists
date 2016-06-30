#include<stdio.h>
#include<stdlib.h>
#include<pthread.h>
#include<signal.h>
#include<errno.h>
#include<string.h>
#include<sys/select.h>
#include<unistd.h>

#include "my402main.h"
#include "my402list.h"
#include "my402tokenhandler.h"
#include "my402packethandler.h"
#include "my402serverhandler.h"
#include "my402functionality.h"

//Global Variables
double lambda,mu,r,tokendrop,packetdrop;
int B,P,total_Packets,total_arv_packets,total_serv_packets,total_tokens_generated;
My402List *Q1,*Q2;
int curB;
char *tracefile;
pthread_mutex_t m=PTHREAD_MUTEX_INITIALIZER;;
pthread_cond_t cond_t;
FILE *tfile;
struct timeval starttime,endtime;
double total_inter_arv,total_time_spent,total_time_spent2,total_service_time,total_time_Q1,total_time_Q2,total_time_S1,total_time_S2;
sigset_t set;
int main(int argc, char *argv[])
{
  initdefaultvalues();
  checkCommandLine(argc,argv);
  printEmulationParameters();
  Q1 = malloc(sizeof(My402List));
  Q2 = malloc(sizeof(My402List));
  My402ListInit(Q1);
  My402ListInit(Q2);
  pthread_t token_thread,packet_thread,server_thread1,server_thread2,sigHandler;
  blockSignal();
  gettimeofday(&starttime,NULL);
  printTimeDiff(starttime);
  printf(" emulation begins\n");
  pthread_create(&token_thread, NULL, tokenhandler, NULL);
  pthread_create(&packet_thread, NULL, packethandler, NULL);
  pthread_create(&server_thread1, NULL, serverhandler, (void *)1);
  pthread_create(&server_thread2, NULL, serverhandler, (void *)2);
  pthread_create(&sigHandler, NULL, signalHandler, NULL);
  pthread_join(token_thread,NULL);
  pthread_join(packet_thread,NULL);
  pthread_join(server_thread1,NULL);
  pthread_join(server_thread2,NULL);
  gettimeofday(&endtime,NULL);
  printStatistics(endtime);
 return 0;
}




void initdefaultvalues()
{
 lambda=1;
 mu=0.35;
 r=1.5;
 B=10;
 P=3;
 total_Packets=20;
 curB=0;
 total_inter_arv=0;
 total_service_time=0;
 total_time_spent=0;
 total_time_spent2=0;
 total_time_Q1=0;
 total_time_Q2=0;
 total_time_S1=0;
 total_time_S2=0;
 total_arv_packets=0;
 total_serv_packets=0;
 total_tokens_generated=0;
 tokendrop=0;
 packetdrop=0;
 tracefile=NULL;
 tfile=NULL;
}

void printEmulationParameters()
{
  printf("Emulation Parameters:\n");
  if(tracefile==NULL)
  {
   printf("\tnumber to arrive = %d\n",total_Packets);
   printf("\tlambda = %g\n",lambda);
   printf("\tmu = %g\n",mu);
   printf("\tr = %g\n",r);
   printf("\tB = %d\n",B);
   printf("\tP = %d\n",P);
  }
  else
  {
   printf("\tnumber to arrive = %d\n",total_Packets);
   printf("\tr = %g\n",r);
   printf("\tB = %d\n",B);
   printf("\ttsfile = %s\n",tracefile);
   }

}

void printStatistics(struct timeval endtime)
{
  double total_emu_time=timediff(starttime,endtime);
  printTimeDiff(endtime);
  printf("emulation ends\n\n");
  printf("Statistics:\n\n");
  printf("\taverage packet inter-arrival time = %.6f\n",(total_inter_arv/total_arv_packets)/1000);
  if(total_serv_packets!=0)
  	printf("\taverage packet service time = %.6f\n\n",(total_service_time/total_serv_packets)/1000);
  else
  	printf("\taverage packet service time = N/A (no packet arrived at this facility)\n\n");
  printf("\taverage number of packets in Q1 = %.6f\n",total_time_Q1/total_emu_time);
  printf("\taverage number of packets in Q2 = %.6f\n",total_time_Q2/total_emu_time);
  printf("\taverage number of packets at S1 = %.6f\n",total_time_S1/total_emu_time);
  printf("\taverage number of packets at S2 = %.6f\n\n",total_time_S2/total_emu_time);
    
  if(total_serv_packets!=0)
    {
    double avg_time_sys=total_time_spent/total_serv_packets;
    printf("\taverage time a packet spent in system = %.6f\n",avg_time_sys);
    printf("\tstandard deviation for time spent in system = %.6f\n\n",calstddev(total_time_spent2,total_time_spent,total_serv_packets));
    }
  else
    {
      printf("\taverage time a packet spent in system = N/A (no packet arrived at this facility)\n");
       printf("\tstandard deviation for time spent in system = N/A (no packet arrived at this facility)\n");
    } 
if(total_tokens_generated!=0)
  	printf("\ttoken drop probability = %.6f\n",tokendrop/total_tokens_generated);
  else
  	printf("\ttoken drop probability = N/A (no packet arrived at this facility)\n");
  

  if(total_arv_packets!=0)
  	printf("\tpacket drop probability = %.6f\n",packetdrop/total_arv_packets);
  else
  	printf("\tpacket drop probability = N/A (no packet arrived at this facility)\n");
  
}

void blockSignal()
{
 sigemptyset(&set);
 sigaddset(&set, SIGINT);
 sigprocmask(SIG_BLOCK, &set, 0);
}

void *signalHandler(void *threadid)
{
 int sig=0;
 My402ListElem * cur=NULL;
 My402Packet *p=NULL;
 struct timeval curtime;
 sigwait(&set, &sig);
 pthread_mutex_lock(&m);
 total_Packets=0;
  for(cur = My402ListFirst(Q2);cur!=NULL;cur=My402ListFirst(Q2))
  {
    p=(My402Packet*)cur->obj;
    gettimeofday(&curtime,NULL);
   My402ListUnlink(Q2,cur);
   printTimeDiff(curtime);
   printf("p%ld removed from Q2\n",p->packet_num );
   free(p);
  }
  for(cur = My402ListFirst(Q1);cur!=NULL;cur=My402ListFirst(Q1))
  {
    p=(My402Packet*)cur->obj;
    gettimeofday(&curtime,NULL);
   My402ListUnlink(Q1,cur);
   printTimeDiff(curtime);
   printf("p%ld removed from Q1\n",p->packet_num );
   free(p);
  }
 pthread_mutex_unlock(&m);
 pthread_cond_broadcast(&cond_t);
 pthread_exit(NULL);
}

