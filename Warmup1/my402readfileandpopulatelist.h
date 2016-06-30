typedef struct{
	
	time_t trans_Time;
	char trans_Type;
	long trans_Amount;
	char *trans_Desc;
		
}My402Elem;

extern int My402ReadFile(FILE* tfile,My402List * list);
void My402ListInsertionSort(My402List *list,My402Elem *obj);
char* trimspace(char *str);
int checkTab(char *str);
