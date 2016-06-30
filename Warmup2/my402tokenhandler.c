#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<pthread.h>
#include<sys/time.h>
#include "my402main.h"
#include "my402functionality.h"
void *tokenhandler(void *threadid)
{
 int token=0;
 struct timeval curTime;
 while(checktotalpackets()||!checkQempty(Q1))
 	{
     double sec=1000000/r;
     usleep(sec);
     if(!checktotalpackets()&&checkQempty(Q1))
         break;
   	 gettimeofday(&curTime,NULL); 
     token++;
     pthread_mutex_lock(&m);
     printTimeDiff(curTime);
     if(curB<B)
       {
         curB++;
         printf("token t%d arrives, token bucket now has %d token\n",token,curB );
       }
     else
       {
         tokendrop++;
         printf("token t%d arrives, dropped\n",token );
       }
     pthread_mutex_unlock(&m);
     checkPacketshift();
     }
 total_tokens_generated=token;
 pthread_exit(NULL);
}

