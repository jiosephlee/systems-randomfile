all: main.o
	gcc -o program main.o
main.o: main.c
	gcc -c main.c
clean:
	rm *.o
	rm *~
run: all
	./program
