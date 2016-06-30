#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "cs402.h"
#include "my402list.h"
#include "my402readfileandpopulatelist.h"
#include "my402formatlist.h"
void printoelem(My402OutputElem *oobj);
int My402createOutputList(My402List* list,My402List* blist)
{ long balance=0;
My402ListElem *elem=NULL;
for (elem=My402ListFirst(list);
                elem != NULL;
                elem=My402ListNext(list, elem)) {
            My402Elem *tobj=(My402Elem*)(elem->obj);
            My402OutputElem *oobj=(My402OutputElem*)malloc(sizeof(My402OutputElem));
            balance+=calculateBalance(tobj);
            formatBalance(oobj,balance);
            formatAmount(oobj,tobj);
            formatTime(tobj,oobj);
            formatDescription(tobj,oobj);
            My402ListAppend(blist,oobj);
            free(tobj);
            }
  return 0;
}
void printoelem(My402OutputElem *oobj)
{
printf("date::%s:%p\n",oobj->trans_Time,&oobj->trans_Time);
printf("amount::%s:%p\n",oobj->trans_Amount,&oobj->trans_Amount);
printf("balance::%s:%p\n",oobj->trans_Balance,&oobj->trans_Balance);
printf("desc::%s:%p\n",oobj->trans_Desc,&oobj->trans_Desc);
}
void formatBalance(My402OutputElem *oobj,long balance)
{
 char *str=(char *)malloc(17*sizeof(char));
 str=longtoformatstring(str,balance);
 if(balance>=1000000000)
  {
   strncpy(str,"  ?,???,???.??  ",16);
  }
  if(balance<0)
   {
   str[14]=')';
   str[1]='(';
   }
 oobj->trans_Balance=str;
}
void formatAmount(My402OutputElem *oobj,My402Elem *tobj)
{
char *str=(char *)malloc(17*sizeof(char));
  str=longtoformatstring(str,tobj->trans_Amount);
   if(tobj->trans_Type=='-')
   {
   str[14]=')';
   str[1]='(';
   }
 oobj->trans_Amount=str;
}
char* longtoformatstring(char* str,long value)
{
 int k,n=13;
 if(value<0)
   value*=-1;
 long val=value;
  str[16]='\0';
  str[15]=' ';
  str[14]=' ';
 while(val!=0)
 {
  if(n==11)
   {
    str[n]='.';
    n--;
   }
  else if (n==3||n==7)
   {
    str[n]=',';
    n--;
   }
  else
  { 
   k=val%10;
   str[n]=k+'0';
   n--;
   val/=10;
  }
 }
  while(n>=0)
  {
   if(n==11)
   {
    str[n]='.';
    n--;
   }
   else if(n==12||n==13||n==10)
   {
    str[n]='0';
    n--;
   }
   else
   {
   str[n]=' ';
   n--;
   }
  } 
  return str;
}
void formatTime(My402Elem *tobj,My402OutputElem *oobj)
{
 char *date=(char *)malloc(16*sizeof(char));
 date=converttime(tobj->trans_Time,date);
 oobj->trans_Time=date;
}
void formatDescription(My402Elem *tobj,My402OutputElem *oobj)
{
 char *desc=(char *)malloc(25*sizeof(char));
 strncpy(desc,tobj->trans_Desc,25);
 desc[strlen(desc)-1]='\0';
 oobj->trans_Desc=desc;
 //free(tobj->trans_Desc);
}
long calculateBalance(My402Elem *tobj)
{
 if(tobj->trans_Type=='+')
   {
    return (tobj->trans_Amount); 
   }
 else
  return -1*(tobj->trans_Amount);
}
char* converttime(time_t ttime,char *date)
{
 char buf[26];
 strncpy(buf, ctime(&ttime), sizeof(buf));
 date[0] = buf[0];
 date[1] = buf[1];
 date[2] = buf[2];
 date[3] = buf[3];
 date[4] = buf[4];
 date[5] = buf[5];
 date[6] = buf[6];
 date[7] = buf[7];
 date[8] = buf[8];
 date[9] = buf[9];
 date[10] = buf[10];
 date[11] = buf[20];
 date[12] = buf[21];
 date[13] = buf[22];
 date[14] = buf[23];
 date[15] = '\0';
 return date;
}
