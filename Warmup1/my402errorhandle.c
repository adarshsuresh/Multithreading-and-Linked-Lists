#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include "my402errorhandle.h"
int errorcheckInputCommand(int errorno)
{
 if(errorno==1)
  return 1;
 if(errorno==-2)
   {
    fprintf(stderr,"Malformed Command\n");
    exit(EXIT_FAILURE);
   }
 else if(errorno==-3)
   {
    fprintf(stderr,"Input file is a directory\n");
    exit(EXIT_FAILURE);
   }
else if(errorno==-4)
   {
    fprintf(stderr,"Input file is improper\n");
    exit(EXIT_FAILURE);
   }
 else if(errorno==-5)
  { 
   fprintf(stderr,"Input file doesnot exist or cannot be accessed\n");
   exit(EXIT_FAILURE);
   }
  else
   {
   fprintf(stderr,"Unknown error\n");
   exit(EXIT_FAILURE);
   }
}
int errorcheckforReadFile(int errorno)
{
 if(errorno==1)
  return 1;
  if(errorno==-1)
   {
    fprintf(stderr,"Unable to allocate memory -%s\n",strerror(errno));
    return 0;
   }
 else if(errorno==-2)
   {
    fprintf(stderr,"Length of file is more than 1024 characters.\n");
    return 0;
   }
 else if(errorno==-3)
   {
    fprintf(stderr,"Transaction type is incorrect.Transaction type can only be + or -.\n");
    return 0;
   }
else if(errorno==-4)
   {
    fprintf(stderr,"Transaction time stamp in the file is bad.\n");
    return 0;
   }
 else if(errorno==-5)
  { 
   fprintf(stderr,"Transaction amount has a value greater than 10 million.\n");
   return 0;
   }
   else if(errorno==-6)
  { 
   fprintf(stderr,"Transaction description has a empty value.\n");
   return 0;
   }
   else if(errorno==-7)
  { 
   fprintf(stderr,"A transaction should have exactly 3 TABS.Not more not less\n");
   return 0;
   }
  else if(errorno==-8)
   {
   fprintf(stderr,"Transaction is formatted incorrectly\n");
   return 0;
   }
   else if(errorno==-9)
   {
   fprintf(stderr,"Transaction amount should have a positive value.\n");
   return 0;
   }
   else
     return 0;
   
}

void unabletoAllocateMemory()
{
 fprintf(stderr,"Unable to allocate memory -%s\n",strerror(errno));
}

void unabletoInitializeList()
{
 fprintf(stderr,"Unable to initialize list\n");
}
