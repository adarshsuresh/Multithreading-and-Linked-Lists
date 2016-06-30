typedef struct{
	
	char* trans_Time;
	char* trans_Amount;
	char* trans_Desc;
	char* trans_Balance;
		
}My402OutputElem;
extern int My402createOutputList(My402List* list,My402List* blist);
void formatTime(My402Elem *tobj,My402OutputElem *oobj);
void formatDescription(My402Elem *tobj,My402OutputElem *oobj);
long calculateBalance(My402Elem *tobj);
void formatBalance(My402OutputElem *oobj,long balance);
void formatAmount(My402OutputElem *oobj,My402Elem *tobj);
int My402CalBalance(My402List* list,My402List* blist);
char* converttime(time_t ttime,char *date);
char* longtoformatstring(char* str,long value);
