double checkNum(char *value);
void checkCommandLine(int argc,char *argv[]);
FILE* getFilePointer(char* tracefile);
void printTimeDiff(struct timeval tv1);
void checkPacketshift();
double timediff(struct timeval t1,struct timeval t2);
int checkQempty(My402List *Q);
int checktotalpackets();
double calstddev(double Ex2,double Ex,int n);
