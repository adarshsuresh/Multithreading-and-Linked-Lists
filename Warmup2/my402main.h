#include <pthread.h>
#include <sys/time.h>
#include "my402list.h"

extern double lambda,mu,r,tokendrop,packetdrop;
extern int B,P,total_Packets,curB,total_arv_packets,total_serv_packets,total_tokens_generated;
extern My402List *Q1,*Q2;
extern pthread_mutex_t m;
extern pthread_cond_t cond_t;	
extern char *tracefile;
extern FILE *tfile;
extern struct timeval starttime;
extern double total_inter_arv,total_service_time,total_time_spent,total_time_spent2,total_time_Q1,total_time_Q2,total_time_S1,total_time_S2;
typedef struct
{
 long packet_num; 
 long inter_arrival_time;
 int tokens;
 long service_time;
 struct timeval parvtime;
 struct timeval eQ1;
 struct timeval eQ2;
 double timeinQ1;
}My402Packet;

void initdefaultvalues();
void printEmulationParameters();
void printStatistics(struct timeval endtime);
void blockSignal();
void *signalHandler(void *);
