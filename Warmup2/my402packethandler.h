extern void *packethandler(void *threadid);
My402Packet * genereatePacket(long packet_num,int tokens,double servicetime);
My402Packet * deterPacket(long packet_num);
My402Packet * tPacket(long packet_num);
void printPacket(My402Packet * pack,struct timeval prevP,struct timeval curtime);
