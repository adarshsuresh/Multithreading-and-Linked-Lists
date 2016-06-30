#include "my402list.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int  My402ListLength(My402List *list)
{return list->num_members;}

int My402ListEmpty(My402List *list)
{return list->num_members<=0;}

My402ListElem *My402ListFirst(My402List* list)
{
 if(My402ListEmpty(list)==FALSE)
  {
   My402ListElem* anch=&(list->anchor);
   return anch->next;
  }
 else
  return NULL;
}

My402ListElem *My402ListLast(My402List* list)
{
 if(My402ListEmpty(list)==FALSE)
  {
   My402ListElem* anch=&(list->anchor);
   return anch->prev;
  }
 else
  return NULL;
}

My402ListElem *My402ListNext(My402List* list, My402ListElem* elem)
{
 if(My402ListLast(list)!=elem)
   return elem->next;
 else
   return NULL;
}

My402ListElem *My402ListPrev(My402List* list, My402ListElem* elem)
{
  if(My402ListFirst(list)!=elem)
  	return elem->prev;
  else
  	return NULL;
}

My402ListElem *My402ListFind(My402List* list, void* obj)
{
 My402ListElem * cur=NULL;
 for(cur = My402ListFirst(list);cur!=NULL;cur=My402ListNext(list,cur))
  {
   if(cur->obj==obj)
     return cur;
  }
 return NULL;
}

int My402ListInit(My402List* list)
{
  My402ListElem* anch= &(list->anchor);
  if(anch==0)
   return FALSE;
  else
   {
    list->num_members=0;
    anch->next=anch;
    anch->prev=anch;
    anch->obj=NULL;
    return TRUE;
   }
}

int  My402ListAppend(My402List * list, void* obj)
{
 My402ListElem* anch= &(list->anchor);
 My402ListElem* lelem= My402ListLast(list);
 My402ListElem* nelem=(My402ListElem*) malloc(sizeof(My402ListElem));
 if(nelem==NULL)
  return FALSE;
 nelem->obj=obj;
 if(lelem==NULL)
  {
   nelem->next= anch;
   nelem->prev= anch;
   anch->next=nelem;
   anch->prev=nelem;
  }
 else
  {
   nelem->next= anch;
   nelem->prev= lelem;
   lelem->next=nelem;
   anch->prev=nelem;
  }
 list->num_members++;
 return TRUE;
}

int  My402ListPrepend(My402List* list, void* obj)
{
 My402ListElem* anch=&(list->anchor);
 My402ListElem* felem=My402ListFirst(list);
 My402ListElem* nelem=(My402ListElem*) malloc(sizeof(My402ListElem));
 if(nelem==NULL)
  return FALSE;
 nelem->obj=obj;
 if(felem==NULL)
  {
   nelem->next=anch;
   nelem->prev=anch;
   anch->next=nelem;
   anch->prev=nelem;
  }
 else
 {
  nelem->next=felem;
  nelem->prev=anch;
  felem->prev=nelem;
  anch->next=nelem;
 }
 list->num_members++;
 return TRUE;
}

void My402ListUnlink(My402List *list, My402ListElem *elem)
{
 if(My402ListEmpty(list) == FALSE)
  {
   My402ListElem *nxtelem = elem->next;
   My402ListElem *preelem = elem->prev;
   preelem->next = nxtelem;
   nxtelem->prev = preelem;
   elem->prev = NULL;
   elem->next = NULL;
   free(elem);
   list->num_members--;
  }		
}

void My402ListUnlinkAll(My402List *list)
{
 while(My402ListEmpty(list)==FALSE)
  {
   My402ListUnlink(list, My402ListFirst(list));
  }
}

int  My402ListInsertAfter(My402List* list, void* obj, My402ListElem* elem)
{
 if(elem==NULL)
  return My402ListAppend(list,obj);
 else
 {
  My402ListElem* nelem=NULL;
  nelem=(My402ListElem*) malloc(sizeof(My402ListElem));
  if(nelem==NULL)
   return FALSE;
  nelem->obj=obj;
  My402ListElem *nxtelem= elem->next;
  nelem->next=nxtelem;
  nelem->prev=elem;
  elem->next=nelem;
  nxtelem->prev=nelem;
  list->num_members++;
 }
 return TRUE;
}

int  My402ListInsertBefore(My402List* list, void* obj, My402ListElem* elem)
{
 if(elem==NULL)
  return My402ListPrepend(list,obj);
 else
  {
   My402ListElem* nelem=(My402ListElem*) malloc(sizeof(My402ListElem));
   if(nelem==NULL)
    return FALSE;
   nelem->obj=obj;
   My402ListElem *prevelem= elem->prev;
   nelem->next=elem;
   nelem->prev=prevelem;
   elem->prev=nelem;
   prevelem->next=nelem;
   list->num_members++;
  }
 return TRUE;
}
