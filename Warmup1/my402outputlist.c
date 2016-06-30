#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <string.h>
#include "my402list.h"
#include "cs402.h"
#include "my402readfileandpopulatelist.h"
#include "my402outputlist.h"
#include "my402formatlist.h"

int printOutput(My402List* list)
{
        
          printSeperationLiine();
          printHeadingLine();
          printSeperationLiine();
          printTransaction(list);
          printSeperationLiine();
        return 0;
}
void printTransaction(My402List* list)
{
My402ListElem *elem=NULL;
int i;
 for (elem=My402ListFirst(list);
                elem != NULL;
                elem=My402ListNext(list, elem)) {
            My402OutputElem *tobj=(My402OutputElem*)(elem->obj);
      for(i=0;i<80;i++)
      { if(i==0||i==18||i==45||i==62||i==79)
          printf("|");
        else if(i==2)
         {
          printf("%s",tobj->trans_Time);
          i+=strlen(tobj->trans_Time)-1;
          free(tobj->trans_Time);
         }
         else if(i==20)
         {
         printf("%s",tobj->trans_Desc);
          i+=strlen(tobj->trans_Desc)-1;
          free(tobj->trans_Desc);
         }
         else if(i==46)
         {
         printf("%s",tobj->trans_Amount);
          i+=strlen(tobj->trans_Amount)-1;
          free(tobj->trans_Amount);
         }
         else if(i==63)
         {
          printf("%s",tobj->trans_Balance);
          i+=strlen(tobj->trans_Balance)-1;
          free(tobj->trans_Balance);
         }
         else
          printf(" ");
     }
     free(tobj);
     printf("\n");
}

void printTransaction(My402List* list)
{
My402ListElem *elem=NULL;
int i;
 for (elem=My402ListFirst(list);
                elem != NULL;
                elem=My402ListNext(list, elem)) {
            My402OutputElem *tobj=(My402OutputElem*)(elem->obj);
      for(i=0;i<80;i++)
      { if(i==0||i==18||i==45||i==62||i==79)
          printf("|");
        else if(i==2)
         {
          printf("%s",tobj->trans_Time);
          i+=strlen(tobj->trans_Time)-1;
         }
         else if(i==20)
         {
         printf("%s",tobj->trans_Desc);
          i+=strlen(tobj->trans_Desc)-1;
         }
         else
          printf(" ");
     }
     printf("\n");
}
}
void printSeperationLiine()
{
int i;
 for(i=0;i<80;i++)
 { if(i==0||i==18||i==45||i==62||i==79)
    printf("+");
  else
   printf("-");}
 printf("\n");  
}
void printHeadingLine()
{
 int i;
 for(i=0;i<80;i++)
 { if(i==0||i==18||i==45||i==62||i==79)
    printf("|");
  else if(i==8)
    { printf("Date");i+=3;}
  else if(i==20)
    { printf("Description");i+=10;}
  else if(i==55)
    { printf("Amount");i+=5;}
  else if(i==71)
    { printf("Balance");i+=6;}
  else 
   printf(" ");
}
 printf("\n");  
}
}
void printSeperationLiine()
{
int i;
 for(i=0;i<80;i++)
 { if(i==0||i==18||i==45||i==62||i==79)
    printf("+");
  else
   printf("-");}
 printf("\n");  
}
void printHeadingLine()
{
 int i;
 for(i=0;i<80;i++)
 { if(i==0||i==18||i==45||i==62||i==79)
    printf("|");
  else if(i==8)
    { printf("Date");i+=3;}
  else if(i==20)
    { printf("Description");i+=10;}
  else if(i==55)
    { printf("Amount");i+=5;}
  else if(i==71)
    { printf("Balance");i+=6;}
  else 
   printf(" ");
}
 printf("\n");  
}
