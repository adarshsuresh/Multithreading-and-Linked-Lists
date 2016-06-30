#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "my402list.h"
#include "cs402.h"
#include "my402errorhandle.h"
#include "my402readfileandpopulatelist.h"

int My402ReadFile(FILE* tfile,My402List * list)
{
 char *line=NULL;
 size_t len=0;
 char * token=NULL;
 int i;
 My402Elem* tobj;
 while (getline(&line, &len, tfile)!= -1)
 {
  if((len=strlen(line))>1024)
   {return -2;}
   if(!checkTab(line))
    return -7;
  token=strtok(line,"\t");
  tobj=(My402Elem *)malloc(sizeof(My402Elem));
  if(tobj==NULL)
    return -1; 
  i=0;
   while(token!=NULL)
   {
    if(i==0)
     {
      if(strcmp(token,"+")==0||strcmp(token,"-")==0)
      {
       char val=token[0];
       tobj->trans_Type=val;
       }
      else 
       return -3;
     } 
    else if(i==1)
     {
      if(strlen(token)>=11)
        return -4;
      int time=(unsigned int)atoi(token);
      tobj->trans_Time=time;
      }
    else if(i==2)
     {
      if(strlen(token)>=11)
        return -5;
      float amt=(float)atof(token);
      amt*=100;
      if(amt<0)
       return -9;
      tobj->trans_Amount=(long)amt; 
      if(tobj->trans_Amount>=1000000000)
       return -5;
     }
    else if(i==3)
     {
      char *desc=(char *)malloc(strlen(token)*sizeof(char));
       strcpy(desc,token);
       desc[strlen(desc)-1]='\0';
      desc=trimspace(desc);
      if(strlen(desc)==0)
       return -6;
      tobj->trans_Desc=desc;
     }
    else
     return -7;
   token=strtok(NULL,"\t");
   i++;
   }
   if(i<=3)
    return -8;
   My402ListInsertionSort(list,tobj);
  }
  return 1;
}
void My402ListInsertionSort(My402List *list,My402Elem *obj)
{
    My402ListElem *elem=NULL;
        for (elem=My402ListFirst(list);elem != NULL;elem=My402ListNext(list, elem)) {
            My402Elem *tobj=(My402Elem*)(elem->obj);
            if(obj->trans_Time<tobj->trans_Time)
              {
               My402ListInsertBefore(list,obj,elem);
               return;
              }
        }
        My402ListAppend(list,obj);
}
int checkTab(char *str)
{
 int i=0;
 int tabCount = 0;
 while(str[i] != '\0')
  {
   if(str[i] == '\t')
    {tabCount++;}
    i++;	
  }
 if(tabCount==3)
  {
   return TRUE;	
  }
 return FALSE;
}
char* trimspace(char *str)
{
while(str[0]==' ') str++; 
return str;
}
