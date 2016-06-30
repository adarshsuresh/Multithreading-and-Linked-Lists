main: my402main.o my402outputlist.o my402formatlist.o my402list.o my402readfileandpopulatelist.o my402errorhandle.o
	gcc -o warmup1 -g my402main.o my402outputlist.o my402formatlist.o my402list.o my402readfileandpopulatelist.o my402errorhandle.o

my402main.o: my402main.c
	gcc -g -c -Wall my402main.c

my402errorhandle.o: my402errorhandle.c my402errorhandle.h
	gcc -g -c -Wall my402errorhandle.c

my402outputlist.o: my402outputlist.c my402outputlist.h
	gcc -g -c -Wall my402outputlist.c
	
my402formatlist.o: my402formatlist.c my402formatlist.h
	gcc -g -c -Wall my402formatlist.c
	
my402readfileandpopulatelist.o: my402readfileandpopulatelist.c my402readfileandpopulatelist.h
	gcc -g -c -Wall my402readfileandpopulatelist.c

my402list.o: my402list.c my402list.h
	gcc -g -c -Wall my402list.c

clean:
	rm -f *.o warmup1 my402main.o my402outputlist.o my402formatlist.o my402readfileandpopulatelist.o my402list.o my402errorhandle.o

