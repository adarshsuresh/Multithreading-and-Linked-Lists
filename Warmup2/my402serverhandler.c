#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include "my402main.h"
#include "my402functionality.h"

void *serverhandler(void *serverno)
{ 
  struct timeval sstime,setime;
  
  while(checktotalpackets()||!checkQempty(Q1)||!checkQempty(Q2)){
   pthread_mutex_lock(&m);
   while(My402ListEmpty(Q2))
   {
     if(total_Packets<=0&&My402ListEmpty(Q1)&&My402ListEmpty(Q2))
     break;
     pthread_cond_wait(&cond_t, &m);
     }
   if(!My402ListEmpty(Q2))
   {
    My402ListElem *elem = My402ListFirst(Q2);
    My402Packet* p = (My402Packet*)(elem->obj);
    My402ListUnlink(Q2, elem);
    gettimeofday(&sstime,NULL);
    double timeQ2=timediff(p->eQ2,sstime);
    total_time_Q2+=timeQ2;
    printTimeDiff(sstime);
    printf("p%ld leaves Q2, time in Q2 = %.3fms\n",p->packet_num,timeQ2);
    gettimeofday(&sstime,NULL);
    printTimeDiff(sstime);
    printf("p%ld begins service at S%d, requesting %ldms of service\n",p->packet_num,(int)serverno,p->service_time/1000);
    pthread_mutex_unlock(&m);
    usleep(p->service_time);
    gettimeofday(&setime,NULL);
    double stime=timediff(sstime,setime);
    double ttime=timediff(p->parvtime,setime);
    if((int)serverno==1)
     {total_time_S1+=stime;}
    else
     {total_time_S2+=stime;}
    pthread_mutex_lock(&m);
    total_time_spent+=ttime/1000;
    total_time_Q1+=p->timeinQ1;
    total_time_spent2+=((ttime/1000)*(ttime/1000));
    total_service_time+=stime;
    printTimeDiff(setime);
    printf("p%ld departs from S%d, service time = %.3fms, time in system = %.3fms\n",p->packet_num,(int)serverno,stime,ttime);
    total_serv_packets++;
    pthread_mutex_unlock(&m);
    free(p);
    }
    else
    {
     pthread_mutex_unlock(&m);
    }
   }
   pthread_exit(NULL);

}
