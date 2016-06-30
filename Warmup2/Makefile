warmup1: my402main.o my402list.o my402tokenhandler.o my402packethandler.o my402serverhandler.o my402functionality.o
	gcc -o warmup2 -g my402main.o my402list.o my402tokenhandler.o my402packethandler.o my402serverhandler.o  my402functionality.o -lm -pthread

my402main.o: my402main.c my402main.h my402list.h  
	gcc -g -c -Wall my402main.c my402list.c
	
my402functionality.o:my402functionality.c my402functionality.h
	gcc -g -c -Wall my402functionality.c 	
	
my402serverhandler.o:my402serverhandler.c my402serverhandler.h
	gcc -g -c -Wall my402serverhandler.c 

my402packethandler.o:my402packethandler.c my402packethandler.h
	gcc -g -c -Wall my402packethandler.c 

my402tokenhandler.o:my402tokenhandler.c my402tokenhandler.h
	gcc -g -c -Wall my402tokenhandler.c 

my402list.o: my402list.c my402list.h
	gcc -g -c -Wall my402list.c

clean:
	rm -f *.o warmup2 
