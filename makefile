all: forkin.o
	gcc forkin.o

forkin.o: forkin.c
	gcc -c forkin.c

clean:
	rm *.o
	rm a.out

run:
	./a.out
