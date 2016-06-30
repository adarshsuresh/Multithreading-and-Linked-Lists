#include <stdio.h>
#include <stddef.h>
#include <stdlib.h>
#include <string.h>
#include <sys/stat.h>
#include <errno.h>
#include "my402list.h"
#include "cs402.h"
#include "my402readfileandpopulatelist.h"
#include "my402outputlist.h"
#include "my402formatlist.h"
#include "my402errorhandle.h"
int checkInputCommand(int argc, char *argv[]);
extern FILE* getFilePointer(FILE* tfile,int argc,char* argv[]); 
int main(int argc,char * argv[])
{
 FILE *tfile=stdin;
 errorcheckInputCommand(checkInputCommand(argc,argv));
 tfile=getFilePointer(tfile,argc,argv);
 My402List* list=(My402List*)malloc (sizeof(My402List));
 if(list==NULL)
  {unabletoAllocateMemory();close(tfile);exit(EXIT_FAILURE);}
 My402List* blist=(My402List*)malloc (sizeof(My402List));
 if(blist==NULL)
  {
  unabletoAllocateMemory();
  close(tfile);
  free(list);
  exit(EXIT_FAILURE);}
 if(!My402ListInit(list))
  {
  unabletoInitializeList();
  free(list);free(blist);close(tfile);
  exit(EXIT_FAILURE);
  } 
  if(!My402ListInit(blist))
   {
  unabletoInitializeList();
  free(list);free(blist);close(tfile);
  exit(EXIT_FAILURE);
  } 
  int retcode=My402ReadFile(tfile,list);
  if(errorcheckforReadFile(retcode))
   {
    My402createOutputList(list,blist);
    printOutput(blist);
    }
  free(list);free(blist);close(tfile);
 return 0;
}

int checkInputCommand(int argc, char *argv[])
{
 
 if(argc==2||argc==3)
 {
  if(strcmp(argv[1],"sort")!=0)
    return -2;
  if(argc==3)
   {
    struct stat fs;
    if( stat(argv[2],&fs) == 0 )
    {
     if(S_ISDIR(fs.st_mode))
      return -3;
     else if(S_ISREG(fs.st_mode))
      return 1;
     else
      return -4;  
    }
    else
     return -5;
   }
   return 1;
 }
 else
    return -2;
}
FILE* getFilePointer(FILE* tfile,int argc,char* argv[])
{
if(argc==3)
   {
    tfile=fopen(argv[2],"r");
    if(tfile==NULL)
     {
      fprintf(stderr,"Input file %s cannot be opened -%s",argv[2],strerror(errno));
      exit(EXIT_FAILURE);
     }
    }
return tfile;
}
